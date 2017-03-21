// FILENAME: BigNum.cxx
// This is the implementation file of the BigNum class


#ifndef HW3_BIGNUM_CXX
#define HW3_BIGNUM_CXX
#include <algorithm>   // Provides copy function
#include <cstdlib>
#include <iostream>
#include <string>
#include <cstring>
#include <cassert>
#include "BigNum.h"
using namespace std;

namespace HW3
{
	BigNum::BigNum()
	{
		capacity = DEFAULT_CAPACITY;
		used = 1;
		positive = true; 
		digits = new unsigned int[capacity];
		digits[0] = 0;		
	}    

	BigNum::BigNum(int num)
	{
		int num2;
		used = 0;
		int i = 0;
		positive = true; 
		if(num < 0)
		{
			positive = false;
			num = -1*num;
		}
		else if(num == 0)
		{
			capacity = DEFAULT_CAPACITY;
			digits = new unsigned int[capacity];
			digits[0] = 0;
			used = 1;
			return;
		}
		
		num2 = num; 
		
		while(num2 > 0)
		{
			num2 /= 10; 
			used++;
		}
		capacity = used+1;

		digits = new unsigned int[capacity];
		while(num > 0)
		{
			digits[i] = num % 10; 
			num /= 10; 
			i++; 
		}
		trim();
	}

	// Constructor that receives a string; leading 0's will be ignored
	BigNum::BigNum(const string& strin)
	{		
		int size = strin.length();
		string copy = strin;  
		capacity = size;
		used = size;
		positive = true; 
		if(copy[0] == '-') 
		{
			positive = false;
			copy.erase(copy.begin());
			used--; 
			size--;
		}
		else if(copy[0] == '+')
		{
			copy.erase(copy.begin());
			used--;
			size--;
		}
		
		while(copy[0] == '0' && size > 1)
		{	
			copy.erase(copy.begin()); 
			size--;
			used--;
		}
	
		digits = new unsigned int[capacity];		
		for(int i = 0; i < size; i++)
			digits[i] = copy[size-i-1] - '0';
		
	}
 
    BigNum::BigNum(const BigNum& anotherBigNum)
    {
		capacity = anotherBigNum.capacity;
		positive = anotherBigNum.positive;
		used = anotherBigNum.used;
		digits = new unsigned int[capacity];
		for(unsigned int i = 0; i < capacity; i++)
		{
			digits[i] = anotherBigNum.digits[i];
		}
    }

    BigNum::~BigNum()
    {
		delete [] digits; 
		digits = NULL;
		capacity = 0; 
		used = 0;
    }
    
    void BigNum::resize(unsigned int n)
	{
		if (n > capacity)
		{
			capacity = n;
			unsigned int* temp = digits; 
			digits = new unsigned int[capacity];
			for(unsigned int i = 0; i < capacity; i++)
				digits[i] = temp[i];
			
			delete [] temp;
		}
	}

	BigNum& BigNum::operator=(const BigNum& anotherBigNum)
	{
		if(this == &anotherBigNum)
			return *this;
		
		positive = anotherBigNum.positive;
		capacity = anotherBigNum.capacity;
		used = anotherBigNum.used;
		delete [] digits;
		digits = new unsigned int[capacity];

		for (unsigned int i = 0; i < capacity; i++)
		{	
			digits[i] = anotherBigNum.digits[i];
		}
		return *this;
	}
  
	BigNum& BigNum::operator+=(const BigNum& addend)  
	{
		*this = *this + addend;
		return *this;
	}

	BigNum& BigNum::operator-=(const BigNum& subtractand)
	{
		*this = *this - subtractand;
		return *this;
	}

	BigNum& BigNum::operator*=(const BigNum& multiplicand)
	{
		*this = (*this) * multiplicand;
		return *this;
	}

	BigNum& BigNum::operator/=(const BigNum& divisor)
	{
		return *this;
	}

	BigNum& BigNum::operator%=(const BigNum& divisor)
	{
		return *this;
	}

	BigNum& BigNum::operator++()
	{
		BigNum one = 1;
		return (*this += one);
	}

	BigNum& BigNum::operator--()
	{
		BigNum one = 1;
		return (*this -= one);
	}

	BigNum& BigNum::diff(const BigNum& a, const BigNum& b)
	{
		BigNum result;
		if(a.used > b.used)
			result.resize(a.used + 1);
		else
			result.resize(b.used + 1);
		int borrow = 0, dif = 0;
		unsigned int i = 0; 
		if(a.used >= b.used)
		{
			while(i < a.used)
			{ 
				if(i < b.used)
				{
					if(a.digits[i] >= b.digits[i]+borrow)
					{
						dif = a.digits[i] - b.digits[i] - borrow;
						borrow = 0;
					}
					else
					{ 
					    dif = a.digits[i] + 10 - b.digits[i] - borrow;
					    borrow = 1; 
					}
					result.digits[i] = dif; 
				}
				else
				{
					if(a.digits[i] == 0 && borrow == 1) 
						result.digits[i] = a.digits[i] + 10 - borrow;
					else
					{
					result.digits[i] = a.digits[i] - borrow;
					borrow = 0;
					}
				}
				i++;
			}
		}
		else
		{
			while(i < b.used)
			{  
				if(i < a.used)
				{
					if(b.digits[i] >= (a.digits[i] + borrow))
					{
						dif = b.digits[i] - a.digits[i] - borrow;
						borrow = 0;
					}
					else
					{ 
					    dif = b.digits[i] + 10 - a.digits[i] - borrow;
					    borrow = 1; 
					}
					result.digits[i] = dif; 
				}
				else
				{
					if(b.digits[i] == 0 && borrow == 1) 
						result.digits[i] = b.digits[i] + 10 - borrow;
					else
					{
					result.digits[i] = b.digits[i] - borrow;
					borrow = 0;
					}
				}
				i++;
			}		
		}
		result.used = i;
		result.trim();
		*this = result;
		return *this;
	}

	BigNum& BigNum::mult(const BigNum& a, const BigNum& b)
	{
		BigNum result = 0, zero = 0, one = 1, neg = -1, temp;
		int carry = 0, prod;
		unsigned int i = 0, k = 0, j;
		if((a == zero) || (b == zero)) //result will be zero
		{
			*this = result;
			return *this;
		}
		else if(a == one) 
		{
			result = b;
			*this = result;
			return *this;
		}
		else if(b == one)
		{
			result = a;
			*this = result;
			return *this;
		}
		else if(a == neg)	//change sign of b
		{
			result = b;
			result.positive = !b.positive;
			*this = result;
			return *this;
		}
		else if(b == neg)  //change sign of a 
		{
			result = a;
			result.positive = !a.positive;
			*this = result;
			return *this;
		}
		if(a.used >= b.used)
		{
			for(i = 0; i < b.used; i++) 
			{
				carry = 0;
				temp = 0;
				temp.resize(a.used + b.used + i);
				if(i > 1) //temp gains 0 
				{	
					for(j = 1; j < i; j++)
						temp.digits[j] = 0;
						temp.used++;
				}
				
				for(k = 0; k < a.used; k++)
				{
					prod = (b.digits[i] * a.digits[k]) + carry;						
					if(prod < 10)
					{
						temp.digits[k+i] = prod;
						carry = 0;
					}
					else
					{	
						temp.digits[k+i] = (prod % 10);
						carry = prod / 10;
						if(k == a.used-1) //last iteration, carry must be stored in next slot
						{
							temp.digits[k+i+1] = carry;
							temp.used++;
						}
					}
					if(k+i > 0) 
						temp.used++;
				}
				result += temp; 
			}
		}
		else
		{
			for(i = 0; i < a.used; i++)
			{
				carry = 0;
				temp = 0;
				temp.resize(a.used + b.used + i);
				if(i > 1)
				{
					for(j = 1; j < i; j++)		
						temp.digits[j] = 0;
						temp.used++;
				}
				
				for(k = 0; k < b.used; k++)
				{
					prod = (a.digits[i] * b.digits[k]) + carry;						
					if(prod < 10)
					{
						temp.digits[k+i] = prod;
						carry = 0;
					}
					else
					{	
						temp.digits[k+i] = (prod % 10);
						carry = prod / 10;
						if(k == b.used-1)
						{
							temp.digits[k+i+1] = carry;
							temp.used++;
						}					
					}
					if(k+i > 0)
						temp.used++;
				}
				result += temp; 
			}
		}
		result.trim();
		*this = result;
		return *this;
	}
	
	BigNum& BigNum::sum(const BigNum& a, const BigNum& b) 
	{
		BigNum result;
		result.resize(a.used + b.used);
		
		unsigned int carry = 0, sum = 0, i = 0;
		while ((i < a.used) || (i < b.used))
		{
			sum = 0;
			if(i < a.used)
				sum += a.digits[i];
			if(i < b.used)
				sum += b.digits[i];
			if(carry > 0)
			{
				sum += carry;
				carry = 0;
			}
			if(sum > 9) //must carry
			{
				carry = sum / 10;
				sum = sum % 10;
				if(a.used >= b.used && i == a.used-1) //at end of bignum, carry must be stored
				{
					result.digits[i] = sum;
					result.digits[i+1] = carry;
					result.used = i+2;
					*this = result;
					return *this;
				}				
				else if(b.used > a.used && i == b.used-1)
				{
					result.digits[i] = sum;
					result.digits[i+1] = carry;
					result.used = i+2;
					*this = result;
					return *this;
				}	
			}	
			result.digits[i] = sum;
			i++;
		}
		result.used = i; 
		*this = result;
		return *this;
	}

	BigNum operator+(const BigNum& a, const BigNum& b)
	{
		BigNum result, zero = 0;

		if(a == zero)
		{
			result = b;
			return result;
		}
		else if(b == zero)
		{
			result = a;
			return result;
		}
		if(a.positive == b.positive) //will add
		{
			result.sum(a, b);
			result.positive = a.positive;
			result.trim();
			return result;	
		}
		else  //opposite signs, deal with substraction
		{
			BigNum aAbs = a, bAbs = b;
			aAbs.positive = true; bAbs.positive = true; //absolute values of a and b
			if(aAbs > bAbs)
			{
				result.diff(a, b);	
				result.positive = a.positive;	
			}
			else if(aAbs < bAbs)
			{
				result.diff(b, a);
				result.positive = b.positive;
			}
			else
			{
				result.positive = true;
				result = 0; //equal and opposite bignums
			}
		}
		result.trim();
		return result;
	}

	BigNum operator-(const BigNum& a, const BigNum& b)
	{
		BigNum result;
		BigNum neg = -1;
		result = a + (neg*b); //use operator+ to do the subtraction
		return result;
		
	}
      
	BigNum operator*(const BigNum& a, const BigNum& b)
	{
		BigNum result;
		result.mult(a, b);
		result.positive = (a.positive == b.positive); //signs must be same to be positive
		result.trim();
		return result;
	}

	BigNum operator / (const BigNum& a, const BigNum& b)
	{
		BigNum result;
		return result;
	}


	BigNum operator%(const BigNum& a, const BigNum& b)
	{
		BigNum result;
		return result;
	}

	bool operator>(const BigNum& a, const BigNum& b)
	{
		if(a.positive > b.positive)
			return true;
		else if(a.positive < b.positive)
			return false;
		
		if(a.used > b.used)
			return true;
		else if(a.used == b.used)
		{	
			int i = a.used-1; 
			if(a.digits[i] > b.digits[i])
				return true;
			else if(b.digits[i] > a.digits[i])
				return false;
			else if(a.digits[i] == b.digits[i])
				while(a.digits[i] == b.digits[i] && i > 0)
				{
					i--;
					if(a.digits[i] > b.digits[i])
						return true;
					else if(a.digits[i] < b.digits[i])
						return false;
				}
		}
		else
			return false;
	}


	bool operator>=(const BigNum& a, const BigNum& b)
	{
		return !(a < b);
	}


	bool operator<(const BigNum& a, const BigNum& b)
	{
		if((a > b) || (a == b))
			return false;
		else 
			return true;
	}


	bool operator<=(const BigNum& a, const BigNum& b)
	{
		if(a < b)
			return true;
		else if(b < a)
			return false;
		else 
			return true;
	}


	bool operator==(const BigNum& a, const BigNum& b)
	{
		if(a > b)
			return false;
		else if(b > a)
			return false;
		else
			return true;
	}


	bool operator!=(const BigNum& a, const BigNum& b)
	{
		return !(a == b);
	}

	// trim leading zeros
	void BigNum::trim()
	{
		while(digits[used-1] == 0 && used > 1)	
		{	
			digits[used-1] = NULL;
			used--;
		}	
	}
	
	
	std::ostream& operator<<(std::ostream &os, const BigNum& bignum)
	{
		if(!bignum.positive && bignum.used >= 1 && bignum.digits[bignum.used -1] != 0)
			os << '-';
		for(unsigned int i = 0; i < bignum.used; i++)
		{
			os << bignum.digits[bignum.used - i -1];
		}
		return os;
	}	 

	std::istream& operator>>(std::istream &is, BigNum& bignum)
	{
		string a;
		is >> a;
		
		BigNum temp = BigNum(a);
		bignum = temp;
		
		return is;
	}
	
	BigNum factorial(const BigNum& a)
	{
		BigNum result;
		return result;
    }
  }



#endif




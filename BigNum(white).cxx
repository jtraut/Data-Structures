// FILENAME: BigNum.cpp
// This is the implementation file of BigNum class


#ifndef HW2_BIGNUM_CXX
#define HW2_BIGNUM_CXX
#include <algorithm>   // Provides copy function
#include <cstdlib>
#include <iostream>
#include <string>
#include <cstring>
#include <cassert>
#include "BigNum.h"
using namespace std;

namespace csci2270_hw2
{
  BigNum::BigNum()
  {
    capacity = DEFAULT_CAPACITY;
    digits = new size_t[capacity]; 
    digits[0] = 0;
    positive = true;      
    used = 1;
  }    

  BigNum::BigNum(int num)
  {
    if(num == 0) {
      positive = true;
      capacity = DEFAULT_CAPACITY;
      digits = new size_t[capacity];
      digits[0] = 0;
      used = 1;
    }
    else {
      if(num > 0) {
        positive = true;
      }
      else {
        positive = false;
        num = -num;
      }
      

      size_t i=0, temp = num;
      while(temp > 0) {
	temp = temp/10; 
	i++;
      }

      // compute closest size that will hold the number
      size_t k = 1;
      while (k * DEFAULT_CAPACITY < i)
      {
	  k *= 2;
      }
      capacity = k * DEFAULT_CAPACITY; 
      digits = new size_t[capacity];
      temp = num;
      for(used=0; used < i; ++used) {
        digits[used] = temp%10;
	temp /= 10;
      }
    }
  }

    // Constructor that receives a character array, leading 0's will be ignored
  BigNum::BigNum(const char strin[])
  {
    int end = 0;
    int len = strlen(strin);
    int i = 0;

    if(strin[0] == '-')  {
      positive = false;
      i = 1;
    }
    else if(strin[0] == '+')  {
      positive = true;
      i = 1;
    }
    else {
      positive = true;
      i = 0;
    }

    while(strin[i] == '0' && i<len)  ++i;
    end = i;

    // if the string is 0
    if(end == len)  {
      used = 1;
      capacity = DEFAULT_CAPACITY;
      digits = new size_t[capacity];
      digits[0] = 0;
      positive = true;
    }    // if the string is not 0
    else {
	used = len-end;
	// compute closest size that will hold the number
	size_t k = 1;
	while (k * DEFAULT_CAPACITY < used)
	{
	    k *= 2;
	}

	capacity = k * DEFAULT_CAPACITY;
	
	digits = new size_t[capacity];

      int start = len-1;
      int j = 0;
      for(int i=start; i>=end; --i) {
        digits[j] = strin[i] - 0x30;
        ++j;
      }
    }
  }
    BigNum::BigNum(const BigNum& anotherBigNum)
    {
	digits = new size_t[anotherBigNum.capacity];
	capacity = anotherBigNum.capacity;
	positive = anotherBigNum.positive;
	used = anotherBigNum.used;
	copy(anotherBigNum.digits, anotherBigNum.digits + used, digits);
    }

    BigNum::~BigNum()
    {
	delete [] digits;
    }
    
    // public function possibly useful in +, * routines
    size_t BigNum::get_digit(size_t index) const
    {
	assert(index < used);
	return digits[index];
    }

    // public function possibly useful in +, * routines
    void BigNum::set_digit(size_t digit, size_t index)
    {
	assert(index < used);
	digits[index] = digit;
    }
    
    // public function possibly useful in +, * routines
    void BigNum::set_used(size_t new_used)
    {
	if (new_used >= capacity)
	{
	    resize(new_used);
	}
	used = new_used;
    }

    // public function possibly useful in +, * routines
    size_t BigNum::get_used() const
    {
	return used;
    }

    // public function possibly useful in +, * routines
    size_t BigNum::get_capacity() const
    {
	return capacity;
    }
    
    bool BigNum::get_positive() const
    {
	return positive;
    }

    void BigNum::set_positive(bool pos_or_neg)
    {
	positive = pos_or_neg;
    }
	
  void BigNum::resize(size_t n)
  {
      // find closest highest size
      size_t k = 1;
      while (k * DEFAULT_CAPACITY < n)
	  k *= 2;
      
    size_t *largerArray;

    if(k * DEFAULT_CAPACITY == capacity)  return;  // The allocated memory is already the right size

    assert(n >= used); // Can't allocate less than we are using

    capacity = k * DEFAULT_CAPACITY; 
    largerArray = new size_t[capacity];
    copy(digits, digits + used, largerArray);
    delete [] digits;
    digits = largerArray;
  }

BigNum& BigNum::operator=(const BigNum &anotherBigNum)
  {
    if(this == &anotherBigNum)  return *this;


    
   // If the memory allocated for this BigNum is not enough to hold all the digits of
   // anotherBigNum, allocate enough memory for this BigNUm

    if(capacity < anotherBigNum.capacity) {
      delete [] digits;
      digits = new size_t[anotherBigNum.capacity];
      capacity = anotherBigNum.capacity;
    }

    positive = anotherBigNum.positive;
    used = anotherBigNum.used;
    copy(anotherBigNum.digits, anotherBigNum.digits + used, digits);
  
    return *this;
  }

  
  BigNum& BigNum::operator+=(const BigNum &addend)  
  {
      *this = *this + addend;
      return *this;
  }


  BigNum& BigNum::operator-=(const BigNum &subtractand)
  {
    *this = *this - subtractand;
    return *this;
  }

  
  BigNum& BigNum::operator*=(const BigNum &multiplicand)
  {
    *this = (*this) * multiplicand;
    return *this;
  }


  BigNum& BigNum::operator/=(const BigNum &divisor)
  {
    *this = (*this) / divisor;
    return *this;
  }


  BigNum& BigNum::operator%=(const BigNum &divisor)
  {
    *this = (*this) % divisor;
    return *this;
  }


  BigNum& BigNum::operator++()
  {
    BigNum temp(1);
    *this = *this + temp;
    return *this;
  }


  BigNum& BigNum::operator--()
  {
    BigNum temp(1);
    *this = *this - temp;
    return *this;
  }


  BigNum BigNum::diff(const BigNum &subtractand) const
  {
	BigNum result;
	size_t diff = 0;
	size_t borrow = 0;
	size_t i = 0;
	for (i = 0; i < get_used(); ++i)
	{
	    if (i < subtractand.get_used())
	    {
		if (get_digit(i) >= subtractand.get_digit(i) + borrow)
		{
		    diff = get_digit(i) - borrow - subtractand.get_digit(i);
		    borrow = 0;
		}
		else
		{
		    diff = get_digit(i) - borrow + 10 - subtractand.get_digit(i);
		    borrow = 1;
		}
	    }
	    else
	    {
		if (get_digit(i) >= borrow)
		{
		    diff = get_digit(i) - borrow;
		    borrow = 0;
		}
		else
		{
		    diff = get_digit(i) + 10 - borrow;
		    borrow = 1;
		}
	    }

	    if (i > result.get_used() - 1)
		result.set_used(result.get_used() + 1);
	    result.set_digit(diff % 10, i);
	}

	
	i = result.get_used() - 1;
	while (i > 0 && result.get_digit(i) == 0)
	{
	    result.set_used(result.get_used() - 1);
	    --i;
	}
	return result;
  }
  

  BigNum BigNum::sum(const BigNum &addend) const
  {
	BigNum result;
	size_t sum = 0;
	size_t carry = 0;
	size_t i = 0;
	for (i = 0; i < get_used() || i < addend.get_used(); ++i)
	{
	    sum = 0;
	    if (i < get_used())
		sum += get_digit(i);
	    if (i < addend.get_used())
		sum += addend.get_digit(i);
	    sum += carry;

	    if (i == result.get_used())
		result.set_used(i + 1);
	    result.set_digit(sum % 10, i);
	    carry = sum / 10;
	}

	if (carry > 0)
	{
	    // cout << i << " carry " << carry << endl;
	    if (i == result.get_used())
		result.set_used(i + 1);
	    result.set_digit(carry, i);
	}

	// cout << result << endl;
	return result;

  }

  BigNum BigNum::operator+(const BigNum &addend) const
  {
      BigNum result;

      if (get_used() == 1 && get_digit(0) == 0)
      {
	  if (addend.get_used() == 1 && addend.get_digit(0) == 0)
	      return result;
	  else
	      return addend;
      }
      if (addend.get_used() == 1 && addend.get_digit(0) == 0)
	  return *this;

      // take care of pos + pos and neg + neg
      if (get_positive() == addend.get_positive())
      {
	  result = sum(addend);
	  result.set_positive(get_positive());
      }
      else
      {
	  // this would be like your less-than code
	  bool addend_bigger = false;
	  if (get_used() < addend.get_used())
	      addend_bigger = true;
	  else
	  {
	      if (get_used() > addend.get_used())
		  addend_bigger = false;
	      else
	      {
		  bool done = false;
		  for (size_t i = get_used() - 1;
		       i > 0 && done == false; --i)
		  {
		      if (get_digit(i) > addend.get_digit(i))
		      {
			  done = true;
			  addend_bigger = false;
		      }
		      else
		      {
			  if (get_digit(i) < addend.get_digit(i))
			  {
			      done = true;
			      addend_bigger = true;
			  }
		      }
		  }
		  if (done == false)
		      addend_bigger = (get_digit(0) < addend.get_digit(0));
	      }
	  }
	  
	  if (addend_bigger)
	  {
	      result = addend.diff(*this);
	      // if *this is positive and addend is bigger in magnitude,
	      // result is negative
	      if (get_positive())
		  result.set_positive(false);
	      else
		  result.set_positive(true);
	  }
	  else
	  {
	      result = diff(addend);
	      // check for zero result
	      if (result.get_used()== 1 && result.get_digit(0) == 0)
	      {
		  result.set_positive(true);
	      }
	      else
	      {
		  // if *this is positive and addend is smaller in magnitude,
		  // result is positive
		  if (get_positive())
		      result.set_positive(true);
		  else
		      result.set_positive(false);
	      }
	  }
      }
      
      return result;
  }


  BigNum BigNum::operator-(const BigNum &subtractand) const
  {
      BigNum result;

      if (get_used() == 1 && get_digit(0) == 0)
      {
	  if (subtractand.get_used() == 1 && subtractand.get_digit(0) == 0)
	      return result;
	  else
	  {
	      result = subtractand;
	      result.set_positive(!subtractand.get_positive());
	      return result;
	  }
      }

      if (subtractand.get_used() == 1 && subtractand.get_digit(0) == 0)
      {
	  return *this;
      }
      
      if (get_positive() != subtractand.get_positive())
      {
	  result = sum(subtractand);
	  result.set_positive(get_positive());
      }
      else
      {
	  // this would be like your less-than code
	  bool subtractand_bigger = false;
	  if (get_used() < subtractand.get_used())
	      subtractand_bigger = true;
	  else
	  {
	      if (get_used() > subtractand.get_used())
		  subtractand_bigger = false;
	      else
	      {
		  bool done = false;
		  for (size_t i = get_used() - 1;
		       i > 0 && done == false; --i)
		  {
		      if (get_digit(i) > subtractand.get_digit(i))
		      {
			  done = true;
			  subtractand_bigger = false;
		      }
		      else
		      {
			  if (get_digit(i) < subtractand.get_digit(i))
			  {
			      done = true;
			      subtractand_bigger = true;
			  }
		      }
		  }
		  if (done == false)
		      subtractand_bigger = (get_digit(0) < subtractand.get_digit(0));
	      }
	  }
	  if (subtractand_bigger == false)
	  {
	      result = diff(subtractand);
	      if (result.get_used() == 1 && result.get_digit(0) == 0)
		  result.set_positive(true);
	      else
	      {
		  if (get_positive())
		      result.set_positive(true);
		  else
		      result.set_positive(false);
	      }
	  }
	  else
	  {
	      result = subtractand.diff(*this);
	      if (result.get_used() == 1 && result.get_digit(0) == 0)
		  result.set_positive(true);
	      else
	      {
		  if (get_positive())
		      result.set_positive(false);
		  else
		      result.set_positive(true);
	      }
	  }
      }
      
      return result;
  }
      

  BigNum BigNum::operator*(const BigNum &multiplicand) const
  {
      	BigNum result = 0;

	size_t product = 0;
	size_t carry;
	size_t i, j, k;

	for (i = 0; i < get_used(); ++i)
	{
	    BigNum int_result;
	    for (k = 0; k < i; ++k)
	    {
		if (k == int_result.get_used())
		    int_result.set_used(k + 1);
		int_result.set_digit(0, k);
	    }
	    
	    carry = 0;
	    for (j = 0; j < multiplicand.get_used(); ++j)
	    {
		product = get_digit(i) * multiplicand.get_digit(j);
		product += carry;
		// cout << i << " " << j << " " << product % 10 << endl;
		if (k + j == int_result.get_used())
		    int_result.set_used(k + j + 1);
		int_result.set_digit(product % 10, k + j);
		carry = product / 10;
	    }

	    while (carry > 0)
	    {
		// cout << k + j << " carry " << carry << endl;
		if (k + j == int_result.get_used())
		    int_result.set_used(k + j + 1);
		int_result.set_digit(carry % 10, k + j);
		carry = carry / 10;
		++k;
	    }

	    //cout << int_result << " ";
	    result = result + int_result;
	    //cout << result << endl;
	}

	i = result.get_used() - 1;
	while (i > 0 && result.get_digit(i) == 0)
	{
	    result.set_used(result.get_used() - 1);
	    --i;
	}
      
	if (get_positive() == multiplicand.get_positive())
	    result.positive = true;
	else
	    result.positive = false;
        return result;
  }


  BigNum BigNum::operator/(const BigNum &divisor) const
  {
    BigNum temp1; 
    if(temp1 == divisor) {
      cout << "Error: divisor is 0!" << endl;
      exit(2);
    }
    if(used == 1 && digits[used] == 0)  return *this;

    BigNum temp2 = *this, temp3 = divisor;
    temp2.positive = true;
    temp3.positive = true;

    if(temp2 < temp3) return temp1;
    if(temp2 >= temp3) {
      while(temp2 >= temp1 * temp3)  ++temp1;
      --temp1;
      if(positive != divisor.positive) temp1.positive = false;
      else temp1.positive = true;
      return temp1;
    }
    return temp1;
 }


  BigNum BigNum::operator%(const BigNum &divisor) const
  {
    return (*this - (*this/divisor) * divisor);
  }


  bool BigNum::operator>(const BigNum &anotherBigNum) const
  {
    if(*this == anotherBigNum)  return false;

    if(get_positive() == true && anotherBigNum.get_positive() == false)  return true;
    else if(get_positive() == false && anotherBigNum.get_positive() == true)  return false;
    else {
      if(used > anotherBigNum.used) {
	  if(get_positive() == true)  return true;
	else  return false;
      }
      else if(used < anotherBigNum.used) {
	  if(get_positive() == true)  return false;
        else  return true;
      }
      else {
        for(size_t i=used-1; i>=0; i--) {
          if(digits[i] > anotherBigNum.digits[i])  {
	      if(get_positive() == true)  return true;
	    else  return false;
          }

          if(digits[i] < anotherBigNum.digits[i])  {
	      if(get_positive() == true)  return false;
            else  return true;
          }
        }
      }          
    }
  }


  bool BigNum::operator>=(const BigNum &anotherBigNum) const
  {
    return ((*this > anotherBigNum) || (*this == anotherBigNum));
  }


  bool BigNum::operator<(const BigNum &anotherBigNum) const
  {
    return !(*this >= anotherBigNum);
  }


  bool BigNum::operator<=(const BigNum &anotherBigNum) const
  {
    return !(*this > anotherBigNum);
  }


  bool BigNum::operator==(const BigNum &anotherBigNum) const
  {
//    if((positive == false) && (anotherBigNum.positive == false))  return true;  // Both BigNums are 0

    if((positive != anotherBigNum.positive) || (used != anotherBigNum.used))
      return false;

    for(size_t i=0; i<used; i++) {
      if(digits[i] != anotherBigNum.digits[i]) 
        return false;
    }

    return true;
  }


  bool BigNum::operator!=(const BigNum &anotherBigNum) const
  {
    return !(*this == anotherBigNum);
  }

  
  BigNum BigNum::factorial() const
  {
    BigNum result = 1;

    if(positive == false) {
      cout<< " Error: Only non-negative BigNums can have factorials." << endl;
      exit(1);
    }
    else if(used == 1 && digits[used] == 0)  return result;
    else {
      for(BigNum i = 1; i<=*this; ++i) {
	  result *= i;
	  //cout << result << endl;
      }
   
      return result;
    }
  }


  std::ostream& operator<<(std::ostream &os, const BigNum &bignum)
  {
      size_t i = 0;
      size_t j = 0;

    if(bignum.positive == false)  cout << '-';

    for(i=0; i<bignum.get_used(); ++i) {
      cout << bignum.get_digit(bignum.get_used() - i - 1);
      if(j<60) ++j; 
      else {
	cout << endl;
	j = 0;
      }
    }
    
    return os;
  } 


  std::istream& operator>>(std::istream &is, BigNum &bignum)
  {
    string str;
    is >> str;

    const char *bignum_str = str.c_str();
    int end = 0;
    int len = strlen(bignum_str);
    int i = 0;
    if(bignum_str[0] == '-')  {
      bignum.positive = false;
      i = 1;
    }
    else if(bignum_str[0] == '+')  {
      bignum.positive = true;
      i = 1;
    }
    else {
      bignum.positive = true;
      i = 0;
    }

    while(bignum_str[i] == '0' && i<len)  ++i;
    end = i;
     
    // if input is 0
    if(end == len)  {
	bignum.used = 1;
	bignum.capacity = bignum.DEFAULT_CAPACITY;
	bignum.digits = new size_t(bignum.capacity);
	bignum.digits[0] = 0;
	bignum.positive = true;
    }
    else {
      bignum.used = len-end;
      // EKW CHANGE
      bignum.resize(bignum.used);

      int start = len-1;
      int j = 0;
      for(int i=start; i>=end; --i) {
        bignum.digits[j] = bignum_str[i] - '0';
	++j;
      }
    } 

    return is;
  }
}

#endif




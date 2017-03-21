

// FILENAME: BigNum.h
// This is the definition of the BigNum class.

// CONSTRUCTORS and DESTRUCTORS for the BigNum class
//
//   BigNum() : Default constructor for the BigNum class. A positive BigNum with default value 0
//      is created after this constructor.
//
//   BigNum(int num) : A BigNum with the same value and sign as num is created after this function.
//
//   BigNum(const string& strin) : A BigNum with the corresponding integer value of string[] is
//      created after this function.
//
//   BigNum(const BigNum& anotherBigNum) : A BigNum with the corresponding interger value of string[] is
//      created after this function.
//
//   ~BigNum() : Dynamic memory allocated for the BigNum is released after this function.
//
// PUBLIC MEMBER FUNCTIONS of the BigNum class:
//
//    BigNum& operator=(const BigNum& anotherBigNum) : The BigNum has been assigned the same value
//       as anotherBigNum after this function is executed.
//
//    BigNum& operator+=(const BigNum& addend) : Addend has been added to this BigNum after this
//       function is executed.
//
//    BigNum& operator-=(const BigNum& subtractand) : Subtractand has been subtracted from this 
//       BigNum after this function is executed.
//
//    BigNum& operator*=(const BigNum& multiplicand) : This BigNum has been multiplied by multiplicand 
//       and the result is stored in this BigNum after this function  is executed.
//
//    BigNum& operator/=(const BigNum& divisor) : This BigNum has been divided by divisor and the
//       result has been stored in this BigNum after this function is executed.
//
//    BigNum& operator%=(const BigNum& divisor) : This BigNum has been taken modulus by divisor and 
//       the result has been stored in this BigNum after this function is executed.
//    
//    BigNum& operator++() : This BigNum has been incremented by 1 after this function is executed.
//
//    BigNum& operator--() : This BigNum has been decremented by 1 after this function is executed.
//
// Private MEMBER FUNCTIONS of the BigNum class:
//
//    void  resize(unsigned int n) : Size of the memory allocated for this BigNum has been changed to n
//      after this function is executed. If n is smaller than the length of this BigNum, this BigNum
//      will not be resized. The n value will be chosen for efficiency; resizing should generally double the
//      number's capacity.
//           
//    BigNum& diff(const BigNum& a, const BigNum& b) : Precondition is that both this BigNum 
//      and subtractand are positive, and also that this BigNum >= subtractand. The result of subtraction
//      has been returned after this function is executed.
//
//    BigNum& sum(const BigNum& a, const BigNum& b) :  Precondition is that both this BigNum
//      and addend are positive. The result of addition has been returned after this function is executed.
//
//    BigNum& mult(const BigNum& a, const BigNum& b) :  Precondition is that both this BigNum
//      and addend are positive. The result of multiplication has been returned after this function is executed.
//
//  FRIEND FUNCTIONS of the BigNum class:
//    friend std::ostream& operator<<(std::ostream &os, const BigNum& bignum) : This bignum has been
//      output to the console after this function is executed.
//
//    friend std::istream& operator>>(std::istream &is, BigNum& bignum) : This BigNum entered from the
//      console has been stored in bignum after this function is executed.
//
//    BigNum operator+(const BigNum& a, const BigNum& b): BigNum a has been added to BigNum b, and
//       neither a nor b has been changed and the result has been returned.
//
//    BigNum operator-(const BigNum& a, const BigNum& b) : BigNum b has been subtracted from BigNum a
//       and neither a nor b has been changed and the result has been returned after 
//       this function is executed. 
//
//    BigNum operator*(const BigNum& a, const BigNum& b) : BigNum a has been multiplied by BigNum b and
//       neither a nor b has been changed and the result has been returned after 
//       this function is executed.
//
//    BigNum operator/(const BigNum& a, const BigNum& b) : BigNum a has been divided by BigNum b and neither a 
//       nor b has been changed and the result has been returned after this function 
//       is executed.
//   
//    BigNum operator%(const BigNum& a, const BigNum& b) : BigNum a has been taken modulus by BigNum b and neither
//       a nor b has been changed and the result has been returned after this function
//       is executed.
//
//    BigNum factorial() : Factorial of this BigNum has been returned after this function is executed.
//
//    bool operator>(const BigNum& a, const BigNum& b) : True will be returned if BigNum a is bigger than
//       BigNum b, otherwise false will be returned.  BigNums a and b will not change.
//
//    bool operator>=(const BigNum& a, const BigNum& b) : True will be returned if BigNum a is greater
//		 than or equal to anotherBigNum, otherwise false will be returned.  BigNums a and b will not change.
//
//    bool operator<(const BigNum& anotherBigNum) :  True will be returned if if BigNum a is smaller than
//       BigNum b, otherwise false will be returned.  BigNums a and b will not change.
//
//    bool operator<=(const BigNum& anotherBigNum) :  True will be returned if if BigNum a is smaller than
//       or equal to BigNum b, otherwise false will be returned.  BigNums a and b will not change.
//
//    bool operator==(const BigNum& anotherBigNum) :  True will be returned if BigNum a is equal to
//       BigNum b, otherwise false will be returned.  BigNums a and b will not change.
//
//    bool operator!=(const BigNum& anotherBigNum) : True will be returned if BigNum a is not equal to
//       BigNum b, otherwise false will be returned.  BigNums a and b will not change.
//



#ifndef HW3_BIGNUM_H
#define HW3_BIGNUM_H
#include <cstdlib>  // Provides unsigned int
#include <iostream> // Provides istream and ostream
#include <cstring>

namespace HW3
{
    class BigNum 
    {
    public:
	
	// CONSTRUCTORS and DESTRUCTORS
	BigNum();                            
	BigNum(int num);                         
	BigNum(const std::string& strin);
	BigNum(const BigNum& anotherBigNum);  
	~BigNum();
	
	
	// MEMBER FUNCTIONS

	BigNum& operator=(const BigNum& anotherBigNum);

	BigNum& operator+=(const BigNum& addend);
	BigNum& operator-=(const BigNum& subtractand);
	BigNum& operator*=(const BigNum& multiplicand);
	BigNum& operator/=(const BigNum& divisor);
	BigNum& operator%=(const BigNum& divisor);
	BigNum& operator++();  // overload prefix increment
	BigNum& operator--();  // overload prefix decrement
	
	// small method used in testing
	char* printBigNum() const {
	    int i = 0;
	    int offset = 0;
	    char* result; 
	    if (!(positive)){
		result = new char[used + 2];
		result[0] = '-';
		offset = 1;
	    }else{
		result = new char[used + 1];
	    }
	    for (i = used - 1; i >= 0 ; --i)
	    {
		result[used - 1 - i + offset] = digits[i] + 48;
	    }
	    result[used + offset] = '\0';
	    return result;
	}

	// FRIEND FUNCTIONS
	friend std::ostream& operator<<(std::ostream& os, const BigNum& bignum);
	friend std::istream& operator>>(std::istream& is, BigNum& bignum);
	friend BigNum operator+(const BigNum& a, const BigNum& b);
	friend BigNum operator-(const BigNum& a, const BigNum& b);
	friend BigNum operator*(const BigNum& a, const BigNum& b);
	friend BigNum operator/(const BigNum& a, const BigNum& b);
	friend BigNum operator%(const BigNum& a, const BigNum& b);
	friend BigNum factorial(const BigNum &a);
	friend bool operator>(const BigNum& a, const BigNum& b);
	friend bool operator>=(const BigNum& a, const BigNum& b);
	friend bool operator<(const BigNum& a, const BigNum& b);
	friend bool operator<=(const BigNum& a, const BigNum& b);
	friend bool operator==(const BigNum& a, const BigNum& b);
	friend bool operator!=(const BigNum& a, const BigNum& b);

	
  private:
	unsigned int *digits;         	// Pointer to the array of BigNum digits 
	bool positive;          		// Indicates the sign of BigNum (true for positive, false for negative)
	unsigned int used;            	// Length of the non-garbage array for BigNum digits  
	unsigned int capacity;        	// Size of the memory allocated for this BigNum 
	static const unsigned int DEFAULT_CAPACITY = 20;

	// not optional
	void resize(unsigned int n);  
	
	// optional helper functions
	void trim();
	BigNum& diff(const BigNum& a, const BigNum& b);
	BigNum& sum(const BigNum& a, const BigNum& b);
	BigNum& mult(const BigNum& a, const BigNum& b);
    };

}

#endif


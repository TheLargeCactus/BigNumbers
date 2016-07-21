#pragma once

#include <vector>
#include <cmath>
#include <iostream>
#include <string>



//BigInt class for holding arbitrarily large numbers
//Class supports all arithmetic operators and all copy and assignment based use
//index 0 is the most significant set of numbers

class BigInt {
private:
	std::vector<unsigned short> number; // container to hold number
	const int MAX_VALUE = 999;//constant to determine max value of each segment of number
	const int MIN_VALUE = 0;
	bool _sign; //0 is a positive number, 1 is a negative number

	bool normal() const;
	
public:
	//constructors

	//default constructor
	//initializes number to 0
	BigInt(void);

	//call constructor0
	//parses a string into a BigInt 
	BigInt(std::string str);

	//copy constructor
	//creates and copies an existing BigInt into this object
	BigInt(const BigInt & param);

	//member functions

	//returns the size of the container, a 3 digit number would have size 3
	int size(void) const;

	//returns the sign of the number
	int sign(void) const;

	//returns true if the number is positive
	bool negative(void) const;

	//change sign of number
	BigInt negate(void) const;

	//function to fix invalid entries
	void normalize();

	//function returns true if value of number is 0
	bool zero() const;

	//utility function for copying data from one BigInt to another
	std::vector<unsigned short> copy(void) const;

	//function to set value of number
	void set(BigInt param);

	void set(std::vector<unsigned short> param);

	void set(short nSign, std::vector<unsigned short> param);

	//function to set sign of number
	void sign(int nSign);

	//function sets the size of the number in base 10 places
	void size(int nSize);

	//operator functions

	//addition operator
	BigInt operator+(const BigInt & rhs);

	//addition assignment operator
	BigInt operator+=(const BigInt & rhs);

	//subtraction operator
	BigInt operator-(const BigInt & rhs);

	//subtraction assignment operator
	BigInt operator-=(const BigInt & rhs);

	//increment pre-fix operator
	BigInt & operator++();

	//increment post-fix operator
	BigInt operator++(int);

	//decrement pre-fix operator
	BigInt & operator--();

	//decrement post-fix operator
	BigInt operator--(int);

	//output stream operator
	friend std::ostream & operator<<(std::ostream & out, const BigInt & rhs);

	//assignment operator
	BigInt & operator=(const BigInt & rhs);

	//boolean operators

	//boolean comparison operator
	bool operator==(const BigInt & rhs);

	//bool not equal operator
	bool operator!=(const BigInt & rhs);

	//boolean less than operator
	bool operator<(const BigInt & rhs);

	//boolean less than or equal to operator
	bool operator<=(const BigInt & rhs);

	//boolean greater than operator
	bool operator>(const BigInt & rhs);

	//boolean greater than or equal to operator
	bool operator>=(const BigInt & rhs);
};
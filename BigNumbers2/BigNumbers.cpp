#include "BigNumbers.h"

void BigInt::normalize()
{
	while (!normal()) {
		if (zero() && negative()) {
			_sign = !_sign;
		}

		for (int i = 0; i < number.size(); i++) {
			if (number[i] > MAX_VALUE) {
				if (i == 0) {
					number.insert(number.begin(), 0);
					number[i + 1] -= MAX_VALUE;
					number[i]++;
				}
				else {
					number[i] -= MAX_VALUE;
					number[i - 1]++;
				}
			}
			else if (number[i] < MIN_VALUE) {
				if (i == 0) {
					_sign = !_sign;
					number[i] = number[i] * -1;
				}
				else {
					number[i - 1]--;
					number[i] += MAX_VALUE;
				}

			}

			if (number.size() > 1 && number[0] == 0) {
				number.erase(number.begin());
			}
		}
	}
} // done

bool BigInt::zero() const
{
	for (int i = 0; i < number.size(); i++) {
		if (number[i] != 0) {
			return false;
		}
	}

	return true;
} //done


bool BigInt::normal() const
{
	if (number.size() > 1 && number[0] == 0) {
		return false;
	}

	if (zero() && negative()) {
		return false;
	}

	for (int i = 0; i < number.size(); i++) {
		if (number[i] > MAX_VALUE || number[i] < MIN_VALUE) {
			return false;
		}
	}

	return true;
} //done

BigInt::BigInt(void)
{
	_sign = 0;
	number.resize(1);
	number[0] = 0;
} // done

BigInt::BigInt(std::string str)
{
	if (str[0] == '-') {
		_sign = 1;
		str.erase(0, 1);
	}
	else {
		_sign = 0;
	}

	while (str.size()) {
		if (str.size() < 3) {
			number.push_back(std::stoi(str.substr(0, str.size())));
			str.erase(str.begin(), str.begin() + str.size());
		}
		else {
			number.push_back(std::stoi(str.substr(0, 3)));
			str.erase(str.begin(), str.begin() + 3);
		}
	}

	normalize();

} // done

BigInt::BigInt(const BigInt & param)
{
	_sign = param.negative();
	number = param.copy();
} // done

int BigInt::size(void) const
{
	return number.size() * 3;
} // done

int BigInt::sign(void) const
{
	return negative() ? -1 : 1;
} // done

bool BigInt::negative(void) const
{
	return _sign; 
}//done


BigInt BigInt::negate(void) const
{
	BigInt temp(*this);

	temp.sign( -1 * negative());

	return temp;
}
// done

std::vector<unsigned short> BigInt::copy(void) const
{
	return number;
} // done

void BigInt::set(BigInt rhs)
{
	_sign = rhs.negative();
	number = rhs.copy();
} // done

void BigInt::set(std::vector<unsigned short> param)
{
	number = param;
} // done

void BigInt::set(short nSign, std::vector<unsigned short> param)
{
	_sign = nSign;
	number = param;
} // done

void BigInt::sign(int nSign)
{
	if (nSign >= 0) {
		_sign = 0;
	}
	else {
		_sign = 1;
	}
} // done

void BigInt::size(int nSize)
{

	if (nSize % 3 == 0) {
		nSize = nSize / 3;
	}
	else {
		nSize = nSize / 3 + 1;
	}

	number.resize(nSize);
} // done

BigInt BigInt::operator+(const BigInt & rhs)
{
	BigInt temp;

	int addsub;

	std::vector<unsigned short> num1 = number;
	std::vector<unsigned short> num2 = rhs.copy();
	std::vector<unsigned short> tempNum;
	
	//set the sign of temp
	if (*this > rhs) {
		temp.sign(sign());
	}
	else {
		temp.sign(rhs.sign());
	}

	//if the signs are different subtract them, else add them
	if (_sign != rhs.negative()) {
		addsub = -1;
	}
	else {
		addsub = 1;
	}

	//normalize sizes
	while (num1.size() < num2.size()) {
		num1.insert(num1.begin(), 0);
	}

	while (num2.size() < num1.size()) {
		num2.insert(num2.begin(), 0);
	}

	tempNum.resize(num1.size());

	for (int i = 0; i < num1.size(); i++) {
		tempNum[i] = num1[i] + addsub * num2[i];
	}

	temp.set(tempNum);
	temp.normalize();

	return temp;
} // done

BigInt BigInt::operator+=(const BigInt & rhs)
{

	int addsub;

	std::vector<unsigned short> num2 = rhs.copy();

	//set the sign of temp
	if (*this > rhs) {
		//do nothing, correct sign will already be set
	}
	else {
		sign(rhs.sign());
	}

	//if the signs are different subtract them, else add them
	if (_sign != rhs.negative()) {
		addsub = -1;
	}
	else {
		addsub = 1;
	}

	//normalize sizes
	while (size() < num2.size()) {
		number.insert(number.begin(), 0);
	}

	while (num2.size() < size()) {
		num2.insert(num2.begin(), 0);
	}

	for (int i = 0; i < number.size(); i++) {
		number[i] += addsub * num2[i];
	}

	normalize();

	return *this;
} // done

BigInt BigInt::operator-(const BigInt & rhs)
{
	BigInt temp;

	int sub1, sub2;

	std::vector<unsigned short> num1 = number;
	std::vector<unsigned short> num2 = rhs.copy();
	std::vector<unsigned short> tempNum;

	//set the sign of temp
	if (*this > rhs) {
		temp.sign(sign());
		sub2 = -1;
		sub1 = 1;
	}
	else {
		temp.sign(rhs.sign());
		sub1 = -1;
		sub2 = 1;
	}

	//normalize sizes
	while (num1.size() < num2.size()) {
		num1.insert(num1.begin(), 0);
	}

	while (num2.size() < num1.size()) {
		num2.insert(num2.begin(), 0);
	}

	tempNum.resize(num1.size());

	for (int i = 0; i < num1.size(); i++) {
		tempNum[i] =  sub1 * num1[i] + sub2 * num2[i];
	}

	temp.set(tempNum);
	temp.normalize();

	return temp;
} // done

BigInt BigInt::operator-=(const BigInt & rhs)
{

	int sub1, sub2;


	std::vector<unsigned short> num2 = rhs.copy();


	//set the sign of this
	if (*this > rhs) {
		sub2 = -1;
		sub1 = 1;
	}
	else {
		sign(rhs.sign());
		sub1 = -1;
		sub2 = 1;
	}

	//normalize sizes
	while (size() < num2.size()) {
		number.insert(number.begin(), 0);
	}

	while (num2.size() < size()) {
		num2.insert(num2.begin(), 0);
	}

	for (int i = 0; i < number.size(); i++) {
		number[i] = sub1 * number[i] + sub2 * num2[i];
	}

	normalize();

	return *this;
} // done

BigInt & BigInt::operator++()
{
	if (_sign) {
		number[number.size() - 1]--;
	}
	else {
		number[number.size() - 1]++;
	}

	normalize();

	return *this;
} // done

BigInt BigInt::operator++(int)
{
	BigInt temp = *this;
	++*this;
	return temp;
} // done

BigInt & BigInt::operator--()
{
	if (_sign) {
		number[number.size() - 1]++;
	}
	else {
		number[number.size() - 1]--;
	}

	normalize();

	return *this;
} // done

BigInt BigInt::operator--(int)
{
	BigInt temp = *this;
	--*this;
	return temp;
} // done

BigInt & BigInt::operator=(const BigInt & rhs)
{
	number = rhs.copy();
	_sign = rhs.sign();

	return *this;
} // done

bool BigInt::operator==(const BigInt & rhs)
{
	return (_sign == rhs.sign() && number == rhs.copy());
} // done

bool BigInt::operator!=(const BigInt & rhs)
{
	return !(*this == rhs);
} // done

bool BigInt::operator<(const BigInt & rhs)
{
	if (sign() < rhs.sign()) {
		return true;
	}
	else if (sign() > rhs.sign()) {
		return false;
	}
	else if (size() < rhs.size()) {
		return true;
	}
	else if (size() > rhs.size()) {
		return false;
	}
	else {
		std::vector<unsigned short> temp = rhs.copy();

		for (int i = 0; i < number.size(); i++) {
			if (number[i] > temp[i]) {
				return false;
			}
			else if (number[i] < temp[i]) {
				return true;
			}
		}

		return false;
	}

	return false;
} // done

bool BigInt::operator<=(const BigInt & rhs)
{
	return (*this == rhs || *this < rhs);
} // done

bool BigInt::operator>(const BigInt & rhs)
{
	return !(*this <= rhs);
} // done

bool BigInt::operator>=(const BigInt & rhs)
{
	return !(*this < rhs);
} // done

std::ostream & operator<<(std::ostream & out, const BigInt & rhs)
{
	if (rhs.negative()) {
		out << '-';
	}

	for (int i = 0; i < rhs.copy().size(); i++) {
		out << rhs.copy()[i];
	}

	return out;
} // done

#pragma once
#include<iostream>
#include<string>
#include<fstream>
#include<cmath>
#include"Number.h"
#define DEFUALT_DENOMINATOR 1
using namespace std;

class Fraction
{
public:
	int m_integerValue;
	int m_numeratorValue;
	int m_denominatorValue;
	string m_stringOfFraction;

	Fraction();
	Fraction(int integer, int numerator, int denominator);
	Fraction(string numStr);
	Fraction(int val);
	Fraction(const Fraction& f);
	string toString();
	Float toFloat();

	//进位操作
	void carryNumerator();

	//约分操作
	void reduceFraction();

	//转换为假分数
	void incrNumerator();

	//取倒数
	void reverseFraction();
	
	//化简操作(进位&约分)
	void simplifyFraction();

	string operator+(Float);
	string operator+(Integer);
	string operator+(Fraction);

	string operator-(Float);
	string operator-(Integer);
	string operator-(Fraction);

	string operator*(Float);
	string operator*(Integer);
	string operator*(Fraction);

	string operator/(Float);
	string operator/(Integer);
	string operator/(Fraction);

};

ostream& operator<<(ostream&,const Fraction&);

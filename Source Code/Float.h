#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include"Number.h"
using namespace std;

class Float
{
public:
	double m_doubleValue;

	Float();
	Float(double val);
	Float(string str);
	Float(const Float& f);
	string toString();

	string operator+(Float);
	string operator+(Integer);
	string operator+(Fraction);

	string operator-(Float);
	string operator-(Integer);
	string operator-(Fraction);

	string operator*(Float);
	string operator*(Integer);
	string operator*(const Fraction);

	string operator/(Float);
	string operator/(Integer);
	string operator/(Fraction);
};

ostream& operator<<(ostream&, Float&);

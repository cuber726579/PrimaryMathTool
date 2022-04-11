#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include"Number.h"
using namespace std;

class Integer
{
public:
	int m_integerValue;

	Integer();
	Integer(int);
	Integer(string);
	Integer(const Integer& i);

	string toString();

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

ostream& operator<<(ostream&, Integer&);
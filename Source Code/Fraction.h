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

	//��λ����
	void carryNumerator();

	//Լ�ֲ���
	void reduceFraction();

	//ת��Ϊ�ٷ���
	void incrNumerator();

	//ȡ����
	void reverseFraction();
	
	//�������(��λ&Լ��)
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

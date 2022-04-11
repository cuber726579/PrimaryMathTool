#include"Integer.h"
#include"Float.h"
#include"Fraction.h"

//构造函数 & 字符串转换
Integer::Integer()
{
	this->m_integerValue = 0;
}
Integer::Integer(int val)
{
	this->m_integerValue = val;
}
Integer::Integer(string str)
{
	this->m_integerValue = stoi(str);
}
Integer::Integer(const Integer& i)
{
	this->m_integerValue = i.m_integerValue;
}
string Integer::toString()
{
	return to_string(this->m_integerValue);
}

//和整数,浮点数,分数的加法
string Integer::operator+(Float num)
{
	return  num + *this;
}
string Integer::operator+(Integer num)
{
	Integer result(this->m_integerValue + num.m_integerValue);
	return  result.toString();
}
string Integer::operator+(Fraction num)
{
	return num + *this;
}

//和整数,浮点数,分数的减法
string Integer::operator-(Float num)
{
	Float result(this->m_integerValue - num.m_doubleValue);
	return result.toString();
}
string Integer::operator-(Integer num)
{
	Integer result(this->m_integerValue - num.m_integerValue);
	return result.toString();
}
string Integer::operator-(Fraction num)
{
	Fraction numInFraction(this->m_integerValue);
	return numInFraction - num;
}

//和整数,浮点数,分数的乘法
string Integer::operator*(Float num)
{
	return num * *this;
}
string Integer::operator*(Integer num)
{
	Integer result(this->m_integerValue * num.m_integerValue);
	return result.toString();
}
string Integer::operator*(Fraction num)
{
	return num * *this;
}

string Integer::operator/(Float num)
{
	Float result(this->m_integerValue / num.m_doubleValue);
	return result.toString();
}
string Integer::operator/(Integer num)
{
	Fraction result(0,this->m_integerValue , num.m_integerValue);
	return result.toString();
}
string Integer::operator/(Fraction num)
{
	Fraction temp = num;
	temp.reverseFraction();
	return *this * temp;
}

ostream& operator<<(ostream& out, Integer& val)
{
	out << val.m_integerValue;
	return out;
}
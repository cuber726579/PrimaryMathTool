#include"Float.h"
#include"Integer.h"
#include"Fraction.h"

Float::	Float()
{
	this->m_doubleValue = 0;
}
Float::Float(double val)
{
	this->m_doubleValue = val;
}
Float::Float(string str)
{
	this->m_doubleValue = stod(str);
}
Float::Float(const Float& f)
{
	this->m_doubleValue = f.m_doubleValue;
}
string Float::toString()
{
	return to_string(this->m_doubleValue);
}

string Float::operator+(Float num)
{
	Float result(this->m_doubleValue + num.m_doubleValue);
	return result.toString();
}
string Float::operator+(Integer num)
{
	Float result(this->m_doubleValue + num.m_integerValue);
	return result.toString();
}
string Float::operator+(Fraction num)
{
	Float result = num.toFloat();
	result.m_doubleValue += this->m_doubleValue;
	return result.toString();
}

string Float::operator-(Float num)
{
	Float result(this->m_doubleValue - num.m_doubleValue);
	return result.toString();
}
string Float::operator-(Integer num)
{
	Float result(this->m_doubleValue - num.m_integerValue);
	return result.toString();
}
string Float::operator-(Fraction num)
{
	Float result(this->m_doubleValue - num.toFloat().m_doubleValue);
	return result.toString();
}

string Float::operator*(Float num)
{
	Float result(this->m_doubleValue * num.m_doubleValue);
	return result.toString();
}
string Float::operator*(Integer num)
{
	Float result(this->m_doubleValue * num.m_integerValue);
	return result.toString();
}
string Float::operator*(Fraction num)
{
	Float result = num.toFloat();
	result.m_doubleValue *= this->m_doubleValue;
	return result.toString();
}

string Float::operator/(Float num)
{
	Float result(this->m_doubleValue / num.m_doubleValue);
	return result.toString();
}
string Float::operator/(Integer num)
{
	Float result(this->m_doubleValue / num.m_integerValue);
	return result.toString();
}
string Float::operator/(Fraction num)
{
	Float temp = num.toFloat();
	Float result(this->m_doubleValue/temp.m_doubleValue);
	return result.toString();
}

ostream& operator<<(ostream& out, Float& val)
{
	out << val.m_doubleValue;
	return out;
}
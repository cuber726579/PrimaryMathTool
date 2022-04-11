#include"Float.h"
#include"Fraction.h"
#include"Integer.h"

Fraction::Fraction()
{
	this->m_integerValue = 0;
	this->m_numeratorValue = 0;
	this->m_denominatorValue = 0;
	this->m_stringOfFraction = this->toString();
}
Fraction::Fraction(int integer, int numerator, int denominator)
{
	this->m_integerValue = integer;
	this->m_numeratorValue = numerator;
	this->m_denominatorValue = denominator;
	this->simplifyFraction();
	this->m_stringOfFraction = this->toString();
}
Fraction::Fraction(string numStr)
{
	this->m_integerValue = 0;
	this->m_numeratorValue = 0;
	this->m_denominatorValue = DEFUALT_DENOMINATOR;

	int underlineIndex = numStr.find("_");
	int barIndex = numStr.find("|");

	//处理整数位
	if(underlineIndex == -1 && barIndex == -1)
		this->m_integerValue = atoi(numStr.c_str());
	else
	{
		string intPart = numStr.substr(0, underlineIndex + 1);
		this->m_integerValue = atoi(intPart.c_str());
	}

	//处理分数位
	if (barIndex != -1)
	{
		string numeratorPart = numStr.substr(underlineIndex + 1, barIndex - underlineIndex - 1);
		string denominatorPart = numStr.substr(barIndex + 1, numStr.length() - barIndex - 1);

		this->m_numeratorValue = atoi(numeratorPart.c_str());
		this->m_denominatorValue = atoi(denominatorPart.c_str());
	}

	this->simplifyFraction();
	this->m_stringOfFraction = this->toString();
}
Fraction::Fraction(int val)
{
	this->m_integerValue = val;
	this->m_numeratorValue = 0;
	this->m_denominatorValue = DEFUALT_DENOMINATOR;
	this->simplifyFraction();
	this->m_stringOfFraction = this->toString();
}
Fraction::Fraction(const Fraction& f)
{
	this->m_integerValue = f.m_integerValue;
	this->m_numeratorValue = f.m_numeratorValue;
	this->m_denominatorValue = f.m_denominatorValue;
}

string Fraction::toString()
{
	this->simplifyFraction();

	string retStr = "";
	if(this->m_integerValue)
		retStr += to_string(this->m_integerValue);

	if (this->m_integerValue && this->m_numeratorValue)
		retStr += "_";

	if (this->m_numeratorValue)
	{
		retStr += to_string(this->m_numeratorValue) + "|";
		retStr += to_string(this->m_denominatorValue);
	}
	return retStr;
}
Float Fraction::toFloat()
{
	Float result;
	result.m_doubleValue = this->m_integerValue + (double)this->m_numeratorValue / this->m_denominatorValue;
	return result;
}

void Fraction::carryNumerator()
{
	int carryNum = this->m_numeratorValue / this->m_denominatorValue;
	this->m_integerValue += carryNum;
	if(carryNum)
		this->m_numeratorValue = abs(this->m_numeratorValue) % this->m_denominatorValue;
}
void Fraction::reduceFraction()
{
	int divisor = gcd(abs(this->m_denominatorValue), abs(this->m_numeratorValue));
	this->m_denominatorValue /= divisor;
	this->m_numeratorValue /= divisor;
}
void Fraction::incrNumerator()
{
	int absValue = abs(this->m_integerValue) * this->m_denominatorValue + this->m_numeratorValue;
	this->m_numeratorValue = this->m_integerValue >= 0 ? absValue : -absValue;
	this->m_integerValue = 0;
}
void Fraction::reverseFraction()
{
	this->incrNumerator();
	int temp = this->m_numeratorValue;
	bool signOfTemp = (temp >= 0);

	this->m_numeratorValue = signOfTemp ? this->m_denominatorValue : -this->m_denominatorValue;
	this->m_denominatorValue = abs(temp);
}
void Fraction::simplifyFraction()
{
	this->carryNumerator();
	this->reduceFraction();
	if ((this->m_numeratorValue < 0 && this->m_denominatorValue < 0) ||
		(this->m_denominatorValue < 0 && this->m_numeratorValue > 0) )
	{
		this->m_denominatorValue = -(this->m_denominatorValue);
		this->m_numeratorValue = -(this->m_numeratorValue);
	}
}

string Fraction::operator+(Float num)
{
	return num + *this;
}
string Fraction::operator+(Integer num)
{
	Fraction result(num.m_integerValue);
	return *this + result;
}
string Fraction::operator+(Fraction num)
{
	//先化为假分数再运算
	Fraction result = *this;
	result.incrNumerator();
	num.incrNumerator();

	int numeratorOfNum = num.m_numeratorValue;
	int commonMultiple = lcm(this->m_denominatorValue, num.m_denominatorValue);

	result.m_numeratorValue *= commonMultiple / result.m_denominatorValue;
	numeratorOfNum *= commonMultiple / num.m_denominatorValue;

	result.m_numeratorValue += numeratorOfNum;
	result.m_denominatorValue = commonMultiple;

	return result.toString();
}

string Fraction::operator-(Float num)
{
	Float result = this->toFloat();
	result.m_doubleValue -= num.m_doubleValue;
	return result.toString();
}
string Fraction::operator-(Integer num)
{
	Fraction numInFraction(num.m_integerValue);

	return *this - numInFraction;
}
string Fraction::operator-(Fraction num)
{
	Fraction result = *this;

	result.incrNumerator();
	num.incrNumerator();

	int commonMultiple = lcm(result.m_denominatorValue, num.m_denominatorValue);

	num.m_numeratorValue *= commonMultiple / num.m_denominatorValue;
	result.m_numeratorValue *= commonMultiple / result.m_denominatorValue;

	result.m_numeratorValue -= num.m_numeratorValue;
	result.m_denominatorValue = commonMultiple;

	return result.toString();
}

string Fraction::operator*(Float num)
{
	return num * *this;
}
string Fraction::operator*(Integer num)
{
	Fraction result = *this;
	result.incrNumerator();
	result.m_numeratorValue *= num.m_integerValue;

	result.simplifyFraction();
	return result.toString();
}
string Fraction::operator*(Fraction num)
{
	Fraction result = *this;
	result.incrNumerator();
	num.incrNumerator();

	result.m_numeratorValue *= num.m_numeratorValue;
	result.m_denominatorValue *= num.m_denominatorValue;

	return result.toString();
}

string Fraction::operator/(Float num)
{
	Float result(this->toFloat().m_doubleValue / num.m_doubleValue);
	return result.toString();
}
string Fraction::operator/(Integer num)
{
	Fraction temp(num.m_integerValue);
	return *this / temp;
}
string Fraction::operator/(Fraction num)
{
	Fraction temp = num;
	temp.reverseFraction();
	return *this * temp;
}

ostream& operator<<(ostream& out,const Fraction& val)
{
	out << val.m_stringOfFraction;
	return out;
}
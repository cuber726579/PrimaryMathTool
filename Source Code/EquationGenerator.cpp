#include"EquationGenerator.h"

EquationGenerator::EquationGenerator(string fileName)
{
	this->m_fileName = fileName;
}

string EquationGenerator::getFileName()
{
	return this->m_fileName;
}

void EquationGenerator::setFileName(string filename)
{
	this->m_fileName = filename;
}

void EquationGenerator::operMenu()
{
	cout << "      =======  生成算术式  =======" << endl;
	cout << "当前读入文件 : " << this->m_fileName << endl;
	cout << "当前输出文件 : " << STANDARD_OUTPUT_FILE << endl;
	cout << "\t----------------------" << endl;
	cout << "\t|                    |" << endl;
	cout << "\t|     1.查看规则     |" << endl;
	cout << "\t|                    |" << endl;
	cout << "\t|     2.生成算术式   |" << endl;
	cout << "\t|                    |" << endl;
	cout << "\t|     0.退    出     |" << endl;
	cout << "\t|                    |" << endl;
	cout << "\t----------------------" << endl;
}

void EquationGenerator::viewRule()
{
	cout << "\t题目类型" << endl;
	cout << "1 --- 整数加减乘除" << endl;
	cout << "2 --- 分数和整数加减乘除" << endl;
	cout << "3 --- 分数、整数和小数加减乘除" << endl;
	cout << "\t读入文件规则" << endl;
	cout << "每行包含两个参数 : 1.题目数量\t2.题目类型" << endl;
	cout << "\t生成算术式规则" << endl;
	cout << "每个算术式包含2 - 5个参数" << endl;
	cout << "每个参数为整数,分数或浮点数" << endl;
}

void EquationGenerator::generateEquation()
{
	srand(time(NULL));
	ifstream ifs(this->m_fileName,ios :: in);
	ofstream ofs(STANDARD_OUTPUT_FILE,ios :: out | ios::app);

	int num, type;
	string buffer;
	getline(ifs, buffer);
	while (ifs >> num && ifs >> type)
	{
		for (int i = 0; i < num; i++)
		{
			string equation;
			switch (type)
			{
				case 1: 
					equation = generateType1(); 
					break;
				case 2: 
					equation = generateType2(); 
					break;
				case 3: 
					equation = generateType3();
					break;
			}
			ofs << equation << " =," << endl;
		}
	}
	ifs.close();
	ofs.close();
}

string EquationGenerator::generateType1()
{
	int num = rand() % 4 + 2;
	string ret = "";
	if (rand() % 2 && num > 2)
	{//有括号
		if (num == 3)
		{
			ret.append("(").append(generateInt(10));
			ret += rand() % 2 ? " + " : " - ";
			ret.append(generateInt(10)).append(")");
			ret += rand() % 2 ? " * " : " / ";
			ret.append(generateInt(10));
		}
		else if(num == 4)
		{
			int flag = 0;
			if (rand() % 2)
			{
				flag = 1;
				ret.append("(").append(generateInt(10));
				ret += rand() % 2 ? " + " : " - ";
				ret.append(generateInt(10)).append(")");
			}
			else
			{
				ret.append(generateInt(10));
				ret += rand() % 2 ? rand() % 2 ? " + " : " - " : rand() % 2 ? " * " : " / ";
				ret.append(generateInt(10));
			}

			ret += rand() % 2 ? " * " : " / ";

			if (!flag || rand() % 2)
			{
				ret.append("(").append(generateInt(10));
				ret += rand() % 2 ? " + " : " / ";
				ret.append(generateInt(10)).append(")");
			}
			else
			{
				ret.append(generateInt(10));
				ret += rand() % 2 ? rand() % 2 ? " + " : " - " : rand() % 2 ? " * " : " / ";
				ret.append(generateInt(10));
			}
		}
		else
		{
			int flag = 0;
			string c1 =  rand() % 2 ? (rand() % 2 ? " + " : " - ") : (rand() % 2 ? " * " : " / ");
			string c2 = (rand() % 2) || !flag ? (rand() % 2 ? " * " : " / ") : (rand() % 2 ? " + " : " - ");
			ret.append("(").append(generateInt(10)).append(c1);
			ret.append(generateInt(10)).append(c2).append(generateInt(10)).append(")");

			string str1 = rand() % 2 ? rand() % 2 ? " + " : " - " : rand() % 2 ? " * " : " / ";
			ret += str1;
			if (rand() % 2 || str1 == " * " || str1 == " / ")
			{
				ret.append("(").append(generateInt(10));
				ret += rand() % 2 ? " + " : " - ";
				ret.append(generateInt(10)).append(")");
			}
			else
			{
				ret.append(generateInt(10));
				ret += rand() % 2 ? (rand() % 2 ? " + " : " - ") : (rand() % 2 ? " * " : " / ");
				ret.append(generateInt(10));
			}
		}
	}
	else
	{//无括号
		for (int i = 0; i < num; i++)
		{
			ret += generateInt(100);
			if (i != num - 1) ret += rand() % 2 ? (rand() % 2 ? " + " : " - ") : (rand() % 2 ? " * " : " / ");
		}
	}
	
	return ret;
}

string EquationGenerator::generateType2()
{
	int num = rand() % 4 + 2;
	string ret = "";
	if (rand() % 2 && num > 2)
	{//有括号
		ret.append("(").append(generateInt(10));
		ret += rand() % 2 ? " + " : " - ";
		ret.append(generateInt(10)).append(")");
		ret += rand() % 2 ? " * " : " / ";
		for (int i = 2; i < num; i++)
		{
			ret += generateFraction();
			if (i != num - 1) ret += rand() % 2 ? (rand() % 2 ? " + " : " - ") : (rand() % 2 ? " * " : " / ");
		}
	}
	else
	{//无括号
		for (int i = 0; i < num; i++)
		{
			ret += generateFraction();
			if (i != num - 1) ret += rand() % 2 ? (rand() % 2 ? " + " : " - ") : (rand() % 2 ? " * " : " / ");
		}
	}

	return ret;
}

string EquationGenerator::generateType3()
{
	int num = rand() % 4 + 2;
	string ret = "";
	if (rand() % 2 && num > 2)
	{//有括号
		ret.append("(").append(generateNumber());
		ret += rand() % 2 ? " + " : " - ";
		ret.append(generateNumber()).append(")");
		ret += rand() % 2 ? " * " : " / ";
		for (int i = 2; i < num; i++)
		{
			ret += generateFraction();
			if (i != num - 1) ret += rand() % 2 ? (rand() % 2 ? " + " : " - ") : (rand() % 2 ? " * " : " / ");
		}
	}
	else
	{//无括号
		for (int i = 0; i < num; i++)
		{
			ret += generateNumber();
			if (i != num - 1) ret += rand() % 2 ? (rand() % 2 ? " + " : " - ") : (rand() % 2 ? " * " : " / ");
		}
	}

	return ret;
}

string EquationGenerator::generateInt(int upperbound)
{
	string ret = "";
	ret.append(to_string(rand() % upperbound + 2));
	return ret;
}

string EquationGenerator::generateFloat()
{
	string ret = "";
	string intPart = to_string(rand() % 10);
	ret.append(intPart).append(".");
	string decimalPart = intPart == "0" ? to_string(rand() % 9 + 1) : to_string(rand() % 10);
	ret.append(decimalPart);
	return ret;
}

string EquationGenerator::generateFraction()
{
	int integer = rand() % 10;
	int denominator = rand() % 7 + 2;
	int numerator = rand() % denominator + 1;
	Fraction f(integer, numerator, denominator);

	string ret = "";
	ret.append(f.toString());
	return ret;
}

string EquationGenerator::generateNumber()
{
	int select = rand() % 3;
	if (select == 0) return generateInt(10);
	else if (select == 1) return generateFraction();
	else return generateFloat();
}

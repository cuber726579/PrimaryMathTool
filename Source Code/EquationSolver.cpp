#include"EquationSolver.h"

EquationSolver::EquationSolver(string inputFile,string outputFile)
{
	ifstream ifs(inputFile, ios::in);
	
	string buffer;
	while (getline(ifs, buffer))
		problemSet.push_back(buffer);

	this->m_outputFile = outputFile;
	ifs.close();
}

EquationSolver::EquationSolver(vector<string> vec)
{
	for (int i = 0; i < vec.size(); i++)
		this->problemSet.push_back(vec[i]);
}

void EquationSolver::operMenu()
{
	cout << "      =======  计算表达式  =======" << endl;
	cout << "当前读入文件 : " << STANDARD_PROBSET_FILE << endl;
	cout << "当前输出文件 : " << this->m_outputFile << endl;
	cout << "\t----------------------" << endl;
	cout << "\t|                    |" << endl;
	cout << "\t|     1.查看规则     |" << endl;
	cout << "\t|                    |" << endl;
	cout << "\t|     2.计算答案     |" << endl;
	cout << "\t----------------------" << endl;
}

void EquationSolver::viewRule()
{
	cout << "\t答案标准" << endl;
	cout << "1 --- 分数化为最简真分数形式" << endl;
	cout << "2 --- 浮点数保留两位小数" << endl;
	cout << "3 --- 分数和整数运算结果为分数形式" << endl;
	cout << "4 --- 分数和整数与浮点数运算结果为浮点数形式" << endl;
}

void EquationSolver::solveEquation()
{
	for (int i = 0; i < problemSet.size(); i++)
	{
		int size = problemSet[i].size();
		if (size == 0) continue;

		stack<char> optrStack;	//操作符
		stack<string> opndStack;//操作数

		for (int j = 0; j < size; j++)
		{
			char data = problemSet[i].at(j);
			string operand;
			while (isdigit(data) || '.' == data || '_' == data || '|' == data)
			{
				operand += data;
				data = problemSet[i].at(++j);
				if (data == ' ' || data == ')')
					opndStack.push(operand);
			}

			if (')' == data)
			{
				data = optrStack.top();
				optrStack.pop();
				while ('(' != data)
				{
					string opnd2 = opndStack.top();
					opndStack.pop();
					string opnd1 = opndStack.top();
					opndStack.pop();

					string result = this->caculate(opnd1, opnd2, data);
					opndStack.push(result);

					data = optrStack.top();
					optrStack.pop();
				}
			}
			else if ('(' == data ||'+' == data || '-' == data || '*' == data || '/' == data)
			{
				if ('(' == data || optrStack.empty())	optrStack.push(data);
				else
				{
					while (!optrStack.empty() && '(' != optrStack.top() && precedence(optrStack.top()) >= precedence(data))
					{
						char topCh = optrStack.top();
						optrStack.pop();

						string opnd2 = opndStack.top();
						opndStack.pop();
						string opnd1 = opndStack.top();
						opndStack.pop();

						string result = this->caculate(opnd1, opnd2, topCh);
						opndStack.push(result);
					}

					optrStack.push(data);
				}
			}
		}

		while (opndStack.size() != 1)
		{
			char optr = optrStack.top();
			optrStack.pop();

			string opnd2 = opndStack.top();
			opndStack.pop();
			string opnd1 = opndStack.top();
			opndStack.pop();

			string result = this->caculate(opnd1, opnd2, optr);
			opndStack.push(result);
		}
		string topStr = opndStack.top();
		int dotPos = topStr.find(".");
		if (-1 != dotPos && topStr[dotPos + 3] >= '5')	topStr[dotPos + 2]++;
		if(-1 != dotPos)	topStr = topStr.substr(0, dotPos + 3);

		problemSet[i].append(topStr).append(",");
	}
}

int EquationSolver::precedence(char data)
{
	int precedence;
	if ('+' == data || '-' == data)
		precedence = 1;
	else
		precedence = 2;
	return precedence;
}

string EquationSolver::caculate(string opnd1, string opnd2, char optr)
{
	if (-1 != opnd1.find("."))
	{//第一个数为浮点数
		Float f1(opnd1);
		if (-1 != opnd2.find("."))
		{
			Float f2(opnd2);
			switch (optr)
			{
				case '+': return f1 + f2;
				case '-': return f1 - f2;
				case '*': return f1 * f2;
				case '/': return f1 / f2;
			}
		}
		else if (-1 != opnd2.find("|"))
		{
			Fraction fc2(opnd2);
			switch (optr)
			{
				case '+': return f1 + fc2;
				case '-': return f1 - fc2;
				case '*': return f1 * fc2;
				case '/': return f1 / fc2;
			}
		}
		else
		{
			Integer i2(opnd2);
			switch (optr)
			{
				case '+': return f1 + i2;
				case '-': return f1 - i2;
				case '*': return f1 * i2;
				case '/': return f1 / i2;
			}
		}
	}
	else if (-1 != opnd1.find("|"))
	{//第一个数为分数
		Fraction fc1(opnd1);
		if (-1 != opnd2.find("."))
		{
			Float f2(opnd2);
			switch (optr)
			{
				case '+': return fc1 + f2;
				case '-': return fc1 - f2;
				case '*': return fc1 * f2;
				case '/': return fc1 / f2;
			}
		}
		else if (-1 != opnd2.find("|"))
		{
			Fraction fc2(opnd2);
			switch (optr)
			{
				case '+': return fc1 + fc2;
				case '-': return fc1 - fc2;
				case '*': return fc1 * fc2;
				case '/': return fc1 / fc2;
			}
		}
		else
		{
			Integer i2(opnd2);
			switch (optr)
			{
				case '+': return fc1 + i2;
				case '-': return fc1 - i2;
				case '*': return fc1 * i2;
				case '/': return fc1 / i2;
			}
		}
	}
	else
	{//第一个数为整数
		Integer i1(opnd1);
		if (-1 != opnd2.find("."))
		{
			Float f2(opnd2);
			switch (optr)
			{
			case '+': return i1 + f2;
			case '-': return i1 - f2;
			case '*': return i1 * f2;
			case '/': return i1 / f2;
			}
		}
		else if (-1 != opnd2.find("|"))
		{
			Fraction fc2(opnd2);
			switch (optr)
			{
			case '+': return i1 + fc2;
			case '-': return i1 - fc2;
			case '*': return i1 * fc2;
			case '/': return i1 / fc2;
			}
		}
		else
		{
			Integer i2(opnd2);
			switch (optr)
			{
			case '+': return i1 + i2;
			case '-': return i1 - i2;
			case '*': return i1 * i2;
			case '/': return i1 / i2;
			}
		}
	}
}

int EquationSolver::problemCounter()
{
	return this->problemSet.size();
}

void EquationSolver::outputToFile()
{
	ofstream ofs(m_outputFile, ios::out | ios::trunc);
	for (int i = 0; i < problemSet.size(); i++)
		ofs << problemSet[i] << endl;
	ofs.close();
}

vector<string> EquationSolver::getAnswer()
{
	vector<string>ret;
	for (int i = 0; i < this->problemSet.size(); i++)
		ret.push_back(problemSet[i]);
	return ret;
}

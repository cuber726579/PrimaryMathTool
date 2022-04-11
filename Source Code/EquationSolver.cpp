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
	cout << "      =======  ������ʽ  =======" << endl;
	cout << "��ǰ�����ļ� : " << STANDARD_PROBSET_FILE << endl;
	cout << "��ǰ����ļ� : " << this->m_outputFile << endl;
	cout << "\t----------------------" << endl;
	cout << "\t|                    |" << endl;
	cout << "\t|     1.�鿴����     |" << endl;
	cout << "\t|                    |" << endl;
	cout << "\t|     2.�����     |" << endl;
	cout << "\t----------------------" << endl;
}

void EquationSolver::viewRule()
{
	cout << "\t�𰸱�׼" << endl;
	cout << "1 --- ������Ϊ����������ʽ" << endl;
	cout << "2 --- ������������λС��" << endl;
	cout << "3 --- ����������������Ϊ������ʽ" << endl;
	cout << "4 --- �����������븡����������Ϊ��������ʽ" << endl;
}

void EquationSolver::solveEquation()
{
	for (int i = 0; i < problemSet.size(); i++)
	{
		int size = problemSet[i].size();
		if (size == 0) continue;

		stack<char> optrStack;	//������
		stack<string> opndStack;//������

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
	{//��һ����Ϊ������
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
	{//��һ����Ϊ����
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
	{//��һ����Ϊ����
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

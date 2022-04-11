#include"AnswerChecker.h"

AnswerChecker::AnswerChecker(string inputFile,string outputFile)
{
	ifstream ifs(inputFile, ios::in);

	string buffer;
	while (getline(ifs, buffer))
	{
		answerSet.push_back(buffer);

		int commaPos = buffer.find_first_of(",");
		problemSet.push_back(buffer.substr(0, commaPos + 1));
	}

	this->m_outputFile = outputFile;
	ifs.close();
}
void AnswerChecker::operMenu()
{
	cout << "      =======  检查答案  =======" << endl;
	cout << "当前读入文件 : " << STANDARD_UNCHECKED_FILE << endl;
	cout << "当前输出文件 : " << this->m_outputFile << endl;
	cout << "\t----------------------" << endl;
	cout << "\t|                    |" << endl;
	cout << "\t|     1.查看规则     |" << endl;
	cout << "\t|                    |" << endl;
	cout << "\t|     2.检查答案     |" << endl;
	cout << "\t----------------------" << endl;
}

void AnswerChecker::viewRule()
{
	cout << "\t检查答案标准" << endl;
	cout << "1 --- 分数需化为最简真分数形式" << endl;
	cout << "2 --- 浮点数保留两位小数" << endl;
	cout << "3 --- 分数和整数运算结果为分数形式" << endl;
	cout << "4 --- 分数和整数与浮点数运算结果为浮点数形式" << endl;
}

int AnswerChecker::checkAnswer()
{
	int correctCount = 0;
	EquationSolver es(this->problemSet);
	es.solveEquation();

	vector<string> answer = es.getAnswer();
	for (int i = 0; i < this->answerSet.size(); i++)
	{
		if (!answer[i].compare(answerSet[i]))
		{
			answerSet[i].append("回答正确!").append(",");
			correctCount++;
		}
		else
			answerSet[i].append("回答错误!").append(",");
	}

	return correctCount;
}

int AnswerChecker::problemCounter()
{
	return this->problemSet.size();
}

void AnswerChecker::outputToFile()
{
	ofstream ofs(m_outputFile, ios::out | ios::trunc);
	for (int i = 0; i < answerSet.size(); i++)
		ofs << answerSet[i] << endl;
	ofs.close();
}

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
	cout << "      =======  ����  =======" << endl;
	cout << "��ǰ�����ļ� : " << STANDARD_UNCHECKED_FILE << endl;
	cout << "��ǰ����ļ� : " << this->m_outputFile << endl;
	cout << "\t----------------------" << endl;
	cout << "\t|                    |" << endl;
	cout << "\t|     1.�鿴����     |" << endl;
	cout << "\t|                    |" << endl;
	cout << "\t|     2.����     |" << endl;
	cout << "\t----------------------" << endl;
}

void AnswerChecker::viewRule()
{
	cout << "\t���𰸱�׼" << endl;
	cout << "1 --- �����軯Ϊ����������ʽ" << endl;
	cout << "2 --- ������������λС��" << endl;
	cout << "3 --- ����������������Ϊ������ʽ" << endl;
	cout << "4 --- �����������븡����������Ϊ��������ʽ" << endl;
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
			answerSet[i].append("�ش���ȷ!").append(",");
			correctCount++;
		}
		else
			answerSet[i].append("�ش����!").append(",");
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

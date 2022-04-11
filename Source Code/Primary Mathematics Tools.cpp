#include<iostream>
#include<fstream>
#include"EquationGenerator.h"
#include"EquationSolver.h"
#include"AnswerChecker.h"
using namespace std;

void mainMenu(void);
void viewRule(void);
void generateEquationMenu(void);
void solveEquationMenu(void);
void checkAnswerMenu(void);

void mainMenu()
{
	cout << "\t----------------------" << endl;
	cout << "\t|                    |" << endl;
	cout << "\t|     1.��������ʽ   |" << endl;
	cout << "\t|                    |" << endl;
	cout << "\t|     2.������ʽ     |" << endl;
	cout << "\t|                    |" << endl;
	cout << "\t|     3.����     |" << endl;
	cout << "\t|                    |" << endl;
	cout << "\t|     4.����˵��     |" << endl;
	cout << "\t|                    |" << endl;
	cout << "\t|     0.��    ��     |" << endl;
	cout << "\t|                    |" << endl;
	cout << "\t----------------------" << endl;
}
void viewRule()
{
	cout << "\t\t�������ļ�����д����\t->" << endl;
	cout << "\t\t��������ʽ\t\t->" << endl;
	cout << "\t\t������ʽ/�ֶ������\t->" << endl;
	cout << "\t\t����,������" << endl;
}
void generateEquationMenu()
{
	string fileName = STANDARD_INPUT_FILE;
	ifstream ifs;
	
	system("pause");
	system("cls");

	int option;
	EquationGenerator eg(fileName);
	while (true)
	{
		eg.operMenu();
		cout << "����������ѡ�� : ";
		cin >> option;

		switch (option)
		{
		case 1:
			eg.viewRule();
			break;
		case 2:
			eg.generateEquation();
			break;
		case 0:
			cout << "\t���˳�����ʽ������,��ӭ�´�ʹ��!" << endl;
			return;
		default:
			cout << "\tError --- ����ѡ����Ч,����������!" << endl;
		}
		system("pause");
		system("cls");
	}

}
void solveEquationMenu()
{
	string fileName = STANDARD_ANS_FILE;

	system("pause");
	system("cls");
	
	int option;
	EquationSolver es(STANDARD_PROBSET_FILE, fileName);
	while (true)
	{
		es.operMenu();
		cout << "����������ѡ�� : ";
		cin >> option;

		switch (option)
		{
		case 1:
			es.viewRule();
			break;
		case 2:
			es.solveEquation();
			es.outputToFile();
			cout << "\t�ѽ��" << es.problemCounter() << "����Ŀ,��ӭ�´�ʹ��!" << endl;
			return;
		default:
			cout << "\tError --- ����ѡ����Ч,����������!" << endl;
		}
		system("pause");
		system("cls");
	}
}
void checkAnswerMenu()
{
	
	string outFile = STANDARD_SCORE_FILE;

	system("pause");
	system("cls");

	int option;
	int correctCount = 0;
	AnswerChecker ac(STANDARD_UNCHECKED_FILE, outFile);
	while (true)
	{
		ac.operMenu();
		cout << "����������ѡ�� : ";
		cin >> option;

		switch (option)
		{
			case 1:
				ac.viewRule();
				break;
			case 2:
				correctCount = ac.checkAnswer();
				ac.outputToFile();
				cout << "�Ѽ��" << ac.problemCounter() << "����Ŀ,������ȷ " << correctCount << " ��!" << endl;
				cout << "\t��ӭ�´�ʹ��!" << endl;
				return;
			default:
				cout << "\tError --- ����ѡ����Ч,����������!" << endl;
		}
		system("pause");
		system("cls");
	}
}

int main(void) 
{
	int option = -1;
	//generateEquationMenu();
	while (true)
	{
		cout << "=======  ��ӭʹ�ó�����ѧ����  =======" << endl;
		mainMenu();
		cout << "����������ѡ�� : ";
		cin >> option;

		switch (option)
		{
			case 1: 
				generateEquationMenu();
				break;
			case 2: 
				solveEquationMenu();
				break;
			case 3: 
				checkAnswerMenu();
				break;
			case 4:
				viewRule();
				break;
			case 0:
				cout << "\t���˳�ϵͳ,��ӭ�´�ʹ��!" << endl;
				return 0;
			default:
				cout << "\tError --- ����ѡ����Ч,����������!" << endl;
		}
		system("pause");
		system("cls");
	}
}
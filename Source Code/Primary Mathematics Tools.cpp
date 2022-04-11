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
	cout << "\t|     1.生成算术式   |" << endl;
	cout << "\t|                    |" << endl;
	cout << "\t|     2.解算术式     |" << endl;
	cout << "\t|                    |" << endl;
	cout << "\t|     3.检查答案     |" << endl;
	cout << "\t|                    |" << endl;
	cout << "\t|     4.流程说明     |" << endl;
	cout << "\t|                    |" << endl;
	cout << "\t|     0.退    出     |" << endl;
	cout << "\t|                    |" << endl;
	cout << "\t----------------------" << endl;
}
void viewRule()
{
	cout << "\t\t在输入文件中填写参数\t->" << endl;
	cout << "\t\t生成算术式\t\t->" << endl;
	cout << "\t\t解算术式/手动填入答案\t->" << endl;
	cout << "\t\t检查答案,输出结果" << endl;
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
		cout << "请输入您的选择 : ";
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
			cout << "\t已退出算术式生成器,欢迎下次使用!" << endl;
			return;
		default:
			cout << "\tError --- 您的选择无效,请重新输入!" << endl;
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
		cout << "请输入您的选择 : ";
		cin >> option;

		switch (option)
		{
		case 1:
			es.viewRule();
			break;
		case 2:
			es.solveEquation();
			es.outputToFile();
			cout << "\t已解答" << es.problemCounter() << "道题目,欢迎下次使用!" << endl;
			return;
		default:
			cout << "\tError --- 您的选择无效,请重新输入!" << endl;
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
		cout << "请输入您的选择 : ";
		cin >> option;

		switch (option)
		{
			case 1:
				ac.viewRule();
				break;
			case 2:
				correctCount = ac.checkAnswer();
				ac.outputToFile();
				cout << "已检查" << ac.problemCounter() << "道题目,其中正确 " << correctCount << " 道!" << endl;
				cout << "\t欢迎下次使用!" << endl;
				return;
			default:
				cout << "\tError --- 您的选择无效,请重新输入!" << endl;
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
		cout << "=======  欢迎使用初级数学工具  =======" << endl;
		mainMenu();
		cout << "请输入您的选择 : ";
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
				cout << "\t已退出系统,欢迎下次使用!" << endl;
				return 0;
			default:
				cout << "\tError --- 您的选择无效,请重新输入!" << endl;
		}
		system("pause");
		system("cls");
	}
}
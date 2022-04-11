#pragma once
#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<stack>
#include<ctype.h>
#include"Integer.h"
#include"Fraction.h"
#include"Float.h"
#define STANDARD_PROBSET_FILE "Standard_ProblemSet_File.csv"
#define STANDARD_ANS_FILE "Standard_AnswerSet_File.csv"
using namespace std;

class EquationSolver
{
private:
	vector<string> problemSet;
	string m_outputFile;
public:
	EquationSolver(string inputFile,string outputFile);
	EquationSolver(vector<string>);

	void operMenu();

	void viewRule();

	void solveEquation();

	int precedence(char);

	string caculate(string,string,char);

	int problemCounter();

	void outputToFile();

	vector<string> getAnswer();
};
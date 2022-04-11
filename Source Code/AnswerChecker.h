#pragma once
#include<iostream>
#include<fstream>
#include<vector>
#include"EquationSolver.h"
#define STANDARD_UNCHECKED_FILE "Standard_AnswerSet_File.csv"
#define STANDARD_SCORE_FILE "Standard_ScoreReport_File.csv"
using namespace std;

class AnswerChecker
{
private:
	vector<string> problemSet;
	vector<string> answerSet;
	string m_outputFile;
public:
	AnswerChecker(string, string);

	void operMenu();

	void viewRule();

	int checkAnswer();

	int problemCounter();

	void outputToFile();
};
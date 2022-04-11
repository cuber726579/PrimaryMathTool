#pragma once
#include<iostream>
#include<fstream>
#include"Integer.h"
#include"Float.h"
#include"Fraction.h"
#define STANDARD_INPUT_FILE "Standard_Input_File.txt"
#define STANDARD_OUTPUT_FILE "Standard_ProblemSet_File.csv"
using namespace std;

class EquationGenerator
{
private:
	string m_fileName;

public:
	EquationGenerator(string fileName);

	string getFileName();

	void setFileName(string filename);

	void operMenu();

	void viewRule();

	void generateEquation();

	string generateType1();

	string generateType2();

	string generateType3();

	string generateInt(int upperbound);

	string generateFloat();

	string generateFraction();

	string generateNumber();
};

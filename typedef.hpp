#ifndef TYPEDEF_HPP
#define TYPEDEF_HPP
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <map>
#include <vector>
#include "symtab.hpp"
using namespace std;

struct OpEntry
{
	string codename;
	int opcode;
	int form;
};

struct AddTable
{
	string codename;
	int form;
};

struct SymTable
{
	string codename;
	int lock;
};

OpEntry get_OpEntry(std::string codename);

void get_Operand1(std::string operand);

void get_Operand2(std::string operand, int r1, int r2);

void get_Operand3(std::string operand, int m);

#endif
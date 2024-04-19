// Source code for assignment 2
// Connor Shands-Sparks - REDID:826895362
// Connor Symons - REDID:828475798

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

struct AddrEntry
{
	string codename;
	int form;
};

struct SymEntry
{
	string codename;
	int lock;
};

OpEntry get_OpEntry(std::string codename);

AddrEntry get_AddrEntry(std::string codename, char prefix);

void get_Format1(std::string op, std::string operand);

void get_Format2(std::string op, std::string operand, int &r1, int &r2);

void get_Format3(std::string op, char prefix, std::string operand, char preop, int linenum, bool &n, bool &i, bool &x, bool &b,bool &p, bool &e, unsigned int &disp);

int findValue(std::string currOperand, Symtab symtab);

void findLitValue(std::string operand, std::string &literal, unsigned long &value, unsigned long &length);

#endif

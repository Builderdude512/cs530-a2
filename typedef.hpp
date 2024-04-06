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

AddrEntry get_AddrEntry(std::string codename);

void get_Format1(std::string op, std::string operand);

void get_Format2(std::string op, std::string operand, int &r1, int &r2);

void get_Format3(std::string op, std::string operand, bool &n, bool &i, bool &x, bool &b,bool &p, bool &e, int &disp);

#endif
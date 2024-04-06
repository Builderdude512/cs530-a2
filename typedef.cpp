#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <map>
#include <vector>
#include "typedef.hpp"
#include "instruction.hpp"
#include "symtab.hpp"
using namespace std;


OpEntry arOpTable[] = {{ "ADD",0x18,0x3},{"ADDF",0x58,0x3},{"ADDR",0x90,0x2},{"AND",0x40,0x3},
{"CLEAR",0xB4,0x2},{"COMP",0x28,0x3},{"COMPF",0x88,0x3},{"COMPR",0xA0,0x2},
{"DIV",0x24,0x3},{"DIVF",0x64,0x3},{"DIVR",0x9C,0x2},{"FIX",0xC4,0x1},
{"FLOAT",0xC0,0x1},{"HIO",0xF4,0x1},{"J",0x3C,0x3},{"JEQ",0x30,0x3},
{"JGT",0x34,0x3},{"JLT",0x38,0x3},{"JSUB",0x48,0x3},{"LDA",0x00,0x3},
{"LDB",0x68,0x3},{"LDCH",0x50,0x3},{"LDF",0x70,0x3},{"LDL",0x08,0x3},
{"LDS",0x6C,0x3},{"LDT",0x74,0x3},{"LDX",0x04,0x3},{"LPS",0xD0,0x3},
{"MUL",0x20,0x3},{"MULF",0x60,0x3},{"MULR",0x98,0x2},{"NORM",0xC8,0x1},
{"OR",0x44,0x3},{"RD",0xD8,0x3},{"RMO",0xAC,0x2},{"RSUB",0x4C,0x3},
{"SHIFTL",0xA4,0x2},{"SHIFTR",0xA8,0x2},{"SIO",0xF0,0x1},{"SSK",0xEC,0x3},
{"STA",0x0C,0x3},{"STB",0x78,0x3},{"STCH",0x54,0x3},{"STF",0x80,0x3},
{"STI",0xD4,0x3},{"STL",0x14,0x3},{"STS",0x7C,0x3},{"STSW",0xE8,0x3},
{"STT",0x84,0x3},{"STX",0x10,0x3},{"SUB",0x1C,0x3},{"SUBF",0x5C,0x3},
{"SUBR",0x94,0x2},{"SVC",0xB0,0x2},{"TD",0xE0,0x3},{"TIO",0xF8,0x1},
{"TIX",0x2C,0x3},{"TIXR",0xB8,0x2},{"WD",0xDC,0x3 }};

AddrEntry arAddTable[] = {{"START",0x0},{"END",0x0},{"BYTE",0x1},{"WORD",0x3},{"RESB",0x1},{"RESW",0x3 }};

SymEntry arSymTable[1000];

OpEntry get_OpEntry(std::string codename){

    for(int i = 0; i<(sizeof(arOpTable)/sizeof(arOpTable[0])); i++) {
        if(codename == arOpTable[i].codename){
			return arOpTable[i];
        }
    }
	//cout << "not found " << codename << "\n";
	return {};
}

AddrEntry get_AddrEntry(std::string codename){

    for(int i = 0; i<(sizeof(arAddTable)/sizeof(arAddTable[0])); i++) {
        if(codename == arAddTable[i].codename){
			return arAddTable[i];
        }
    }
	//cout << "not found " << codename << "\n";
	return {};
}

void get_Format1(std::string op, std::string operand){
    //Nothing Needed
}

void get_Format2(std::string op, std::string operand, int &r1, int &r2) {
 //TODO: figure out r1 and r2 from op and operand
}

void get_Format3(std::string op, std::string operand, bool &n, bool &i, bool &x, bool &b,bool &p, bool &e, int &disp){
 //TODO: Convert op and operand to bools and disp
}
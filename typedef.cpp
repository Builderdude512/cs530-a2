// Source code for assignment 2
// Connor Shands-Sparks - REDID:
// Connor Symons - REDID:828475798

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <map>
#include <vector>
#include <queue>
#include "typedef.hpp"
#include "instruction.hpp"
#include "symtab.hpp"
using namespace std;

extern Symtab symtab;
extern bool baseSet;
extern int baseAddr;

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

AddrEntry arAddTable[] = {{"START",0x0},{"END",0x0},{"BYTE",0x1},{"WORD",0x3},{"RESB",0x1},{"RESW",0x3 },
                          {"BASE",0x0},{"ORG",0x0},{"EQU",0x0},{"NOBASE",0x0},{"*",0x0}};

SymEntry arSymTable[1000];

OpEntry get_OpEntry(std::string codename, char prefix){
    for(size_t i = 0; i<(sizeof(arOpTable)/sizeof(arOpTable[0])); i++) {
        if(codename == arOpTable[i].codename){
            auto temp = arOpTable[i];
            if (prefix == '+') {
                temp.form = 4;
            }
			return temp;
        }
    }
	//cout << "not found " << codename << "\n";
	return {};
}

AddrEntry get_AddrEntry(std::string codename, char prefix){

    for(size_t i = 0; i<(sizeof(arAddTable)/sizeof(arAddTable[0])); i++) {
        if(codename == arAddTable[i].codename){
			return arAddTable[i];
        }
    }
	//cout << "not found " << codename << "\n";
	return {};
}

void get_Format1(std::string /* op */, std::string /* operand */){
    //Nothing Needed
}

//These solutions assume 'op' contains just the opcode and 'operand' contains all other arguments without any whitespace
void get_Format2(std::string op, std::string operand, int &r1, int &r2) {
    size_t pos;
    std::string currRegister;

    //case where only 1 register is given, cannot use ',' as delimiter, r2 is set to 0
    if(op == "CLEAR" || op == "SVC" || op == "TIXR") {\
        //with no whitespace, operand should just be the first register ie "A"
        currRegister = operand;

        //for SVC interrupt, r1 = n, not an actual register
        if(op == "SVC") {
            r1 = stoi(currRegister);
            r2 = 0;
            return;
        }

        //set value of r1
        if(currRegister == "A")
            r1 = 0;
        else if(currRegister == "X")
            r1 = 1;
        else if(currRegister == "L")
            r1 = 2;
        else if(currRegister == "B")
            r1 = 3;
        else if(currRegister == "S")
            r1 = 4;
        else if(currRegister == "T")
            r1 = 5;
        else if(currRegister == "F")
            r1 = 6;
        else if(currRegister == "PC")
            r1 = 8;
        else if(currRegister == "SW")
            r1 = 9;
        else {
            return;
        }
        r2 = 0;
        return;
    }

    //get first register using ',' as delimiter
    pos = operand.find(',');
    currRegister = operand.substr(0, pos);
    //set r1 based on register found
    if(currRegister == "A")
        r1 = 0;
    else if(currRegister == "X")
        r1 = 1;
    else if(currRegister == "L")
        r1 = 2;
    else if(currRegister == "B")
        r1 = 3;
    else if(currRegister == "S")
        r1 = 4;
    else if(currRegister == "T")
        r1 = 5;
    else if(currRegister == "F")
        r1 = 6;
    else if(currRegister == "PC")
        r1 = 8;
    else if(currRegister == "SW")
        r1 = 9;
    else {
        return;
    }


    //get second register, from first character after ',' to end
    currRegister = operand.substr(pos + 1);

    //case where second part of operand is actually a shift amount, pass n-1 to r2 as specified by appendix A
    if(op == "SHIFTL" || op == "SHIFTR") {
        r2 = stoi(currRegister);
        return;
    }

    //set r2 based on register found
    if(currRegister == "A")
        r2 = 0;
    else if(currRegister == "X")
        r2 = 1;
    else if(currRegister == "L")
        r2 = 2;
    else if(currRegister == "B")
        r2 = 3;
    else if(currRegister == "S")
        r2 = 4;
    else if(currRegister == "T")
        r2 = 5;
    else if(currRegister == "F")
        r2 = 6;
    else if(currRegister == "PC")
        r2 = 8;
    else if(currRegister == "SW")
        r2 = 9;
    else
        cout << "bad operand, found " << currRegister;
}

//again assumes no whitespace
//added linenum argument for PC-relative addressing
void get_Format3(std::string op, char prefix, std::string operand, char preop, int linenum, bool &n, bool &i, bool &x, bool &b,bool &p, bool &e, int &disp){
    std::string currOperand = operand;
    std::queue<string> operandArr;
    std::queue<char> operatorArr;
    int m = 0;

    //set n & i to true, change if not simple addressing
    n = true;
    i = true;


    //RSUB instruction has no operand, sets everything else to 0.
    if(op == "RSUB") {
        x = false;
        b = false;
        p = false;
        e = false;
        disp = 0;
        return;
    }

    //check for n
    if(preop == '@') {
        i = false;
    }

    //check for i
    if(preop == '#') {
        n = false;
    }

    //check for x
    if(operand.length() > 2 && operand.substr(operand.length()-2) == ",x") {
        x = true;
        currOperand = currOperand.substr(0, operand.length()-2);
    }
    else {
        x = false;
    }
    //check for e
    if(prefix == '+') {
        e = true;
    }
    else {
        e = false;
    }

    //control structure for b/p flags, don't enter if immediate/direct addressing mode is selected
    if(n && !e) {
        if(baseSet) {
            b = true;
            p = false;
        }
        else {
            b = false;
            p = true;
        }
    }

    //get raw operand value
    m = findValue(currOperand, symtab);

    //use raw value and flags to find disp
    //if base/PC relative, use correct case, otherwise use direct addressing (disp = raw value)
    if(b) {
        disp = m - baseAddr;
    } else  if (p) {
        //subtract PC value from raw value, which will be 3 more than the current line number
        disp = m - (linenum + 3);
    }
    else {
        disp = m;
    }
}

void get_AddrFormat1(std::string /* op */, std::string /* operand */ /*, and so on- similar to r1 and r2 above*/) {

}
void get_AddrFormat0(std::string /* op */, std::string /* operand */ /*, and so on- similar to r1 and r2 above*/) {

}
void get_AddrFormat3(std::string /* op */, std::string /* operand */ /*, and so on- similar to r1 and r2 above*/) {

}

//helper method to process operand value
int findValue(std::string currOperand, Symtab symtab) {
    int m = 0;
    int currValue;
    std::queue<string> operandArr;
    std::queue<char> operatorArr;
    bool leadingNegativeTerm = false;
    //check if the first term is negative
    if(currOperand.length() > 0 && currOperand.at(0) == '-') {
        leadingNegativeTerm = true;
        currOperand = currOperand.substr(1);
    }


    //tokenize operand for cases where multiple values are added/subtracted from each other
    while(currOperand.length() > 0) {
        unsigned long long j;
        //loop over operand until '+' or '-' is found
        for(j = 0; j < currOperand.length(); j++) {
            //if operator found, add it to operator array, add preceding term to operand array
            if(currOperand.at(j) == '+' || currOperand.at(j) == '-') {
                operatorArr.push(currOperand.at(j));
                operandArr.push(currOperand.substr(0,j));
                break;
            }
        }
        //if no operator found, add remaining operand as the last term in operand array
        if(j == currOperand.length()) {
            operandArr.push(currOperand);
            j--;
        }
        //remove added portion from currOperand
        currOperand = currOperand.substr(j+1);
    }


    //find raw value of operand
    //try to return value if it is an int literal, catch and find value in SYMTAB if not int literal
    try {
        currValue = stoi(operandArr.front());
    }
    catch (std::exception& e) {
        //checks to see if entry exists in symtab (which it should) before grabbing value
        if(symtab.values.find(operandArr.front()) != symtab.values.end()) {
            currValue = symtab.values[operandArr.front()];
        }
        else
            currValue = 0;
    }
    //add/subtract leading term
    if(!leadingNegativeTerm) {
        m += currValue;
    }
    else {

        m -= currValue;
    }
    operandArr.pop();


    //iterate over remaining operand elements
    while(!operandArr.empty()) {
        try {
            currValue = stoi(operandArr.front());
        }
        catch (std::exception& e) {
            //checks to see if entry exists in symtab (which it should) before grabbing value
            if(symtab.values.find(operandArr.front()) != symtab.values.end()) {
                currValue = symtab.values[operandArr.front()];
            }
            else
                currValue = 0;
        }
        if(operatorArr.front() == '+') {
            m += currValue;
        } else if (operatorArr.front() == '-') {
            m -= currValue;
        }
        operandArr.pop();
        operatorArr.pop();
    }
    return m;
}
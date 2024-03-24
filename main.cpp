// Your First C++ Program

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <map>
#include <vector>
#include "instruction.hpp"
#include "symtab.hpp"
using namespace std;

// TODO: read SIC files, output ST files and I files


bool first_pass(Symtab & symtab);
bool second_pass(Symtab & symtab);


int main() {

    Symtab symtab;

    fstream sicfile;
    // TODO: open file
    string line, line2;
    vector<string> holder;

    while(std::getline(sicfile, line)) {
        line2 = line.substr(10);
        std::istringstream iss(line2);
        string op, operand;
        iss >> op;
        iss >> operand;
        // TODO: read column by column, pass1 looking for symbols, pass2 do something different for each different opcode
    }


    bool ok = first_pass(symtab);
    if(!ok) {
        return 1;
    }
    ok = second_pass(symtab);
    if(!ok) {
        return 1;
    }
    return 0;
}

bool first_pass(Symtab & /*symtab*/) 
{
    printf("first\n") ;
    // TODO: read all lines, looking for symbols, put length and value to symbol table
    return true;
}

bool second_pass(Symtab & /*symtab*/) 
{
    printf("second\n") ;
    // TODO: read each line and output assembly statement for each line
    // TODO: handle start statement
    // TODO: handle LDX
    // TODO: handle LDA
    // TODO: handle +LDB
    // TODO: handle BASE
    // TODO: handle ADD
    // TODO: handle ADD
    // TODO: handle TIX
    // TODO: handle JLT
    // TODO: handle +STA
    // TODO: handle RSUB
    // TODO: handle +LDA
    // TODO: handle RESW
    // TODO: handle RESW
    // TODO: handle RESW
    // TODO: handle RESW
    // TODO: handle =C'EOF'
    // TODO: handle END
    return true;
}

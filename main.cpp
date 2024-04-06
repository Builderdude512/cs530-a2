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


bool first_pass(Symtab & symtab, string flnm);
bool second_pass(Symtab & symtab, string flnm);


int main() {

    Symtab symtab;
    string flnm = "data/files/P2sample.sic";

    bool ok = first_pass(symtab, flnm);
    if(!ok) {
        return 1;
    }
    ok = second_pass(symtab, flnm);
    if(!ok) {
        return 1;
    }
    return 0;
}

bool first_pass(Symtab & /*symtab*/, string /*flnm*/) 
{
    printf("first\n") ;
    // TODO: read all lines, looking for symbols, put length and value to symbol table, to be done in the future
    return true;
}

bool second_pass(Symtab & /*symtab*/, string flnm) 
{
    printf("second\n") ;
    std::cout << flnm << std::endl;
    fstream sicfile(flnm);
    // TODO: open file
    string line, line2;
    vector<string> holder;
    string op, operand;
    // TODO: Keep track of line number to pass to instruction
    while(std::getline(sicfile, line)) {
        Instruction instruct(line);
        std::cout << instruct.op << " " << instruct.operand << std::endl;
        // TODO: at this point i've passed the op and operand to Instruction
    }

    
    
    return true;
}

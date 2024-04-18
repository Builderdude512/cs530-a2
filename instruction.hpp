// Source code for assignment 2
// Connor Shands-Sparks - REDID:826895362
// Connor Symons - REDID:828475798

#ifndef INSTRUCTION_HPP
#define INSTRUCTION_HPP
#include "typedef.hpp"
#include <map>
#include <string>

std::string get_op(std::string line, char &prefix);

std::string get_operand(std::string line, char &preop);

std::string get_label(std::string line);

struct Instruction{
    Instruction (std::string line) : line(line), op(get_op(line, prefix)), operand(get_operand(line, preop)){
        OpEntry entry = get_OpEntry(op, prefix);
        if (entry.codename == op){
            //the get_Format functions take the op and operand and change the class's values
            if(entry.form == 1) {
                get_Format1(op, operand);
            } else if (entry.form == 2) {
                get_Format2(op, operand, r1, r2);
            } else if (entry.form == 3) {
                cout << line << "\n";
                get_Format3(op, prefix, operand, preop, linenum, n,i,x,b,p,e,disp); 
            }
        }
        else {
            AddrEntry entry = get_AddrEntry(op, prefix);
            // TODO: Make a parallel function to above with AddrEntry
        }

    }

    std::string line, op, operand;
    int linenum = 0;
    int m = 0;
    int nn = 0;
    int r1 = 0;
    int r2 = 0;
    bool n = false;
    bool i = false;
    bool x = false;
    bool b = false;
    bool p = false;
    bool e = false;
    char prefix = 0;
    char preop = 0;
    int disp = 0;

    // TODO: add Mnemonics, label, start address, and length, alongside decoding all of the above variables

};

#endif 
#ifndef INSTRUCTION_HPP
#define INSTRUCTION_HPP
#include "typedef.hpp"
#include <map>
#include <string>

std::string get_op(std::string line);

std::string get_operand(std::string line);

struct Instruction{
    Instruction (std::string line) : line(line), op(get_op(line)), operand(get_operand(line)){
        OpEntry entry = get_OpEntry(op);
        if (entry.codename == op){
            
            if(entry.form == 1) {
                get_Format1(op, operand);
            } else if (entry.form == 2) {
                get_Format2(op, operand, r1, r2);
            } else if (entry.form == 3) {
                get_Format3(op, operand, n,i,x,b,p,e,disp);
                // pass 
            }
        }
        else {
            AddrEntry entry = get_AddrEntry(op);
            // TODO: Make a parallel function to above with AddrEntry
            if(entry.form == 1) {
                
            } else if (entry.form == 0) {
                
            } else if (entry.form == 3) {
                
                // pass 
            }
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
    int disp = 0;

    // TODO: add Mnemonics, label, start address, and length, alongside decoding all of the above variables

};

#endif 
#ifndef INSTRUCTION_HPP
#define INSTRUCTION_HPP
#include "typedef.hpp"
#include <map>
#include <string>

std::string get_op(std::string line, char &prefix);

std::string get_operand(std::string line, char &prefix);

std::string get_label(std::string line);

struct Instruction{
    Instruction (std::string line) : line(line), op(get_op(line, prefix)), operand(get_operand(line, prefix)){
        OpEntry entry = get_OpEntry(op, prefix);
        if (entry.codename == op){
            //the get_Format functions take the op and operand and change the class's values
            if(entry.form == 1) {
                get_Format1(op, operand);
            } else if (entry.form == 2) {
                get_Format2(op, operand, r1, r2);
            } else if (entry.form == 3) {
                get_Format3(op, operand, n,i,x,b,p,e,disp); 
            }
        }
        else {
            AddrEntry entry = get_AddrEntry(op, prefix);
            // TODO: Make a parallel function to above with AddrEntry
            if(entry.form == 1) {
                get_AddrFormat1(op, operand /*, and so on- similar to r1 and r2 above*/);
            } else if (entry.form == 0) {
                get_AddrFormat0(op, operand /*, and so on- similar to r1 and r2 above*/);
            } else if (entry.form == 3) {
                get_AddrFormat3(op, operand /*, and so on- similar to r1 and r2 above*/);
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
    char prefix = 0;
    int disp = 0;

    // TODO: add Mnemonics, label, start address, and length, alongside decoding all of the above variables

};

#endif 
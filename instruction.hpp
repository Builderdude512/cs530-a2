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
                
            } else if (entry.form == 2) {

            } else if (entry.form == 3) {

            }
        }
        else {
            AddrEntry entry = get_AddrEntry(op);
        }
        // TODO: look to third entry, format. if style 2, then two operands, if style 3, then one, else none
    }

    std::string line, op, operand;
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

    // TODO: add Mnemonics, label, start address, and length, alongside decoding all of the above variables

};

#endif 
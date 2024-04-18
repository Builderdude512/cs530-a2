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
        formatType = entry.form;
        if (entry.codename == op){
            //the get_Format functions take the op and operand and change the class's values
            if(entry.form == 1) {
                get_Format1(op, operand);
            } else if (entry.form == 2) {
                get_Format2(op, operand, r1, r2);
            } else if (entry.form == 3) {
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
    unsigned int disp = 0;
    int formatType = -1;

    // TODO: add Mnemonics, label, start address, and length, alongside decoding all of the above variables

    std::string get_instform()
    {
        char buffer[256];

        if (formatType == -1) {
            return "";
        } else if (formatType == 1) {
            sprintf(buffer, "%02x", get_OpEntry(op, prefix).opcode);
        } else if (formatType == 2) {
            sprintf(buffer, "%02x%01x%01x", get_OpEntry(op, prefix).opcode, r1, r2);
        } else if (formatType == 3) {
            unsigned char instruct;
            unsigned short instruct2 = disp;
            instruct = get_OpEntry(op, prefix).opcode;
            if (n) {
                instruct |= 2;
            }
            if (i) {
                instruct |= 1;
            }
            if (x) {
                instruct2 |= 0x8000;
            }
            if (b) {
                instruct2 |= 0x4000;
            }
            if (p) {
                instruct2 |= 0x2000;
            }
            if (e) {
                instruct2 |= 0x1000;
            }
            
            sprintf(buffer, "%02x%04x", instruct, instruct2);
            cout << instruct << " \n";
        } else if (formatType == 4) {
            unsigned char instruct;
            unsigned int instruct2 = disp;
            instruct = get_OpEntry(op, prefix).opcode;
            if (n) {
                instruct |= 2;
            }
            if (i) {
                instruct |= 1;
            }
            if (x) {
                instruct2 |= 0x800000;
            }
            if (b) {
                instruct2 |= 0x400000;
            }
            if (p) {
                instruct2 |= 0x200000;
            }
            if (e) {
                instruct2 |= 0x100000;
            }
            
            sprintf(buffer, "%02x%06x", instruct, instruct2);
            cout << instruct << " \n";
        } 

        std::string result = buffer;
        return result;
    }

};



#endif 
#ifndef INSTRUCTION_HPP
#define INSTRUCTION_HPP
#include <map>
#include <string>

std::string get_op(std::string line)
{
    std::string line2 = line.substr(10);
    std::istringstream iss(line2);
    std::string op, operand;
    iss >> op;
    return op;
}

std::string get_operand(std::string line)
{
    std::string line2 = line.substr(10);
    std::istringstream iss(line2);
    std::string op, operand;
    iss >> op;
    iss >> operand;
    return operand;
}

struct Instruction{
    Instruction (std::string line) : line(line), op(get_op(line)), operand(get_operand(line)){
        
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
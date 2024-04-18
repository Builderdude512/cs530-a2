// Source code for assignment 2
// Connor Shands-Sparks - REDID:826895362
// Connor Symons - REDID:828475798

#include "instruction.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <map>
#include <vector>

std::string get_op(std::string line, char &prefix)
{
    std::string line2 = line.substr(10);
    std::istringstream iss(line2);
    std::string op, operand;
    iss >> op;
    if (line[9] == '+' || line[9] == '=') {
        prefix = line[9];
    }
    return op;
}

std::string get_operand(std::string line, char &prefix)
{
    std::string line2 = line.substr(10);
    std::istringstream iss(line2);
    std::string op, operand;
    iss >> op;
    iss >> operand;
    if (line[17] == '@' || line[17] == '#' || line[17] == '=') {
        prefix = line[17];
        operand = operand.substr(1);
    }
    return operand;
}

std::string get_label(std::string line)
{
    if(line[0] == ' ') {
        return "";
    }
    std::istringstream iss(line);
    std::string label;
    iss >> label;
    return label;
}

std::string replaceUppercase(std::string instruction)
{
    for(char& c : instruction) {
        if(c >= 97 && c <= 102) {
            c -= 32;
        }
    }
    return instruction;
}

std::string get_instform();
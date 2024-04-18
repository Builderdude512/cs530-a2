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
        cout << prefix << " \n";
    } else if(line[9] != '+') {
        prefix = '@';
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
    if (line[18] == '@' || line[18] == '#') {
        prefix = line[18];
    } else {
        prefix = '0';
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

std::string get_instform()
{

}
#include "instruction.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <map>
#include <vector>

std::string get_op(std::string line)
{
    std::string line2 = line.substr(10);
    std::istringstream iss(line2);
    std::string op, operand;
    iss >> op;
    if (line[9] == '+') {
        op = "+" + op;
    }
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
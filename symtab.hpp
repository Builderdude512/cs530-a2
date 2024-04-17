// Source code for assignment 2
// Connor Shands-Sparks - REDID:
// Connor Symons - REDID:828475798

#ifndef SYMTAB_HPP
#define SYMTAB_HPP
#include <map>
#include <string>

struct Symtab{
    std::map<std::string, int> values;
    std::map<std::string, int> lengths;
};


#endif 
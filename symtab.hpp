#ifndef SYMTAB_HPP
#define SYMTAB_HPP
#include <map>
#include <string>

struct Symtab{
    std::map<std::string, int> values;
    std::map<std::string, int> lengths;
};


#endif 
// Your First C++ Program

#include <iostream>
#include <map>
using namespace std;

class Symtab{
    map<string, int> values;
    map<string, int> lengths;
};

bool first_pass(Symtab & symtab);
bool second_pass(Symtab & symtab);


int main() {

    Symtab symtab;

    bool ok = first_pass(symtab);
    if(!ok) {
        return 1;
    }
    ok = second_pass(symtab);
    if(!ok) {
        return 1;
    }
    return 0;
}

bool first_pass(Symtab & symtab) 
{
    printf("first\n") ;
    return true;
}

bool second_pass(Symtab & symtab) 
{
    printf("second\n") ;
    return true;
}

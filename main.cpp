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
    // TODO: read all lines, looking for symbols, put length and value to symbol table
    return true;
}

bool second_pass(Symtab & symtab) 
{
    printf("second\n") ;
    // TODO: read each line and output assembly statement for each line
    // TODO: handle start statement
    // TODO: handle LDX
    // TODO: handle LDA
    // TODO: handle +LDB
    // TODO: handle BASE
    // TODO: handle ADD
    // TODO: handle ADD
    // TODO: handle TIX
    // TODO: handle JLT
    // TODO: handle +STA
    // TODO: handle RSUB
    // TODO: handle +LDA
    // TODO: handle RESW
    // TODO: handle RESW
    // TODO: handle RESW
    // TODO: handle RESW
    // TODO: handle =C'EOF'
    // TODO: handle END
    return true;
}

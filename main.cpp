// Your First C++ Program

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <map>
#include <vector>
#include "instruction.hpp"
#include "symtab.hpp"
#include <iterator>
using namespace std;

// TODO: read SIC files, output ST files and I files


bool first_pass(Symtab & symtab, string flnm);
bool second_pass(Symtab & symtab, string flnm);
Symtab symtab;


int main() {

    string flnm = "data/files/P2sample.sic";

    bool ok = first_pass(symtab, flnm);
    if(!ok) {
        return 1;
    }
    ok = second_pass(symtab, flnm);
    if(!ok) {
        return 1;
    }
    return 0;
}

bool first_pass(Symtab & /*symtab*/, string flnm) 
{
    printf("first\n") ;
    std::cout << flnm << std::endl;
    fstream sicfile(flnm);
    string line, line2;
    int run_total = 0;
    vector<string> holder;
    string op, operand;

    while(std::getline(sicfile, line)) {
        char prefix = 0;
        char preop = 0;
        std::string label = get_label(line);
        std::string op = get_op(line, prefix);
        std::string operand = get_operand(line, preop);
        OpEntry entry = get_OpEntry(op, prefix);
        if (label.size() > 0) {
            symtab.values[label] = run_total;
            /* cout << "label = " << label << " " << std::hex << run_total << "\n"; */
        }
        if (entry.codename == op){
           run_total += entry.form;
        } else {
            AddrEntry entry = get_AddrEntry(op, prefix);
            if (entry.codename == "START") {
                run_total = 0;
            } else if (entry.codename == "END") {
                
            } else if (entry.codename == "BYTE" || entry.codename == "BASE") {
                run_total += 1;
            } else if (entry.codename == "WORD") {
                run_total += 2;
            } else if (entry.codename == "RESB") {
                run_total += stoi(operand);
            } else if (entry.codename == "RESW") {
                run_total += 2*stoi(operand);
            } 
            
        }

    }

    printf("%-10s%-10s%-10s%-10s%-10s\n", "CSect", "Symbol", "Value", "LENGTH", "Flags");
    printf("--------------------------------------\n");


    /* while ()
    {
        if(output = addrentry)
            output AddrEntry
    } */
    map<string, int>::iterator it;
    for (it = symtab.values.begin(); it != symtab.values.end(); it++)
    {
        auto label = it->first;
        auto location = it->second;
        printf("%-15s%-15s%-15x%-15s%-15s\n", "", label.c_str(), location, "", "");
    }

    return true;
}

bool second_pass(Symtab & /*symtab*/, string flnm) 
{
    printf("second\n") ;
    std::cout << flnm << std::endl;
    fstream sicfile(flnm);
    // TODO: open file
    string line, line2;
    vector<string> holder;
    string op, operand;
    // TODO: Keep track of line number to pass to instruction
    while(std::getline(sicfile, line)) {
        Instruction instruct(line);
        std::cout << instruct.op << " " << instruct.operand << std::endl;
        // TODO: at this point i've passed the op and operand to Instruction
    }

    
    
    return true;
}


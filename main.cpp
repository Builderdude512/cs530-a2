// Source code for assignment 2
// Connor Shands-Sparks - REDID:826895362
// Connor Symons - REDID:828475798

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <filesystem>
#include <iomanip>
#include <utility>
#include <map>
#include <vector>
#include "instruction.hpp"
#include "symtab.hpp"
#include <iterator>
using namespace std;

// TODO: read SIC files, output ST files and I files


bool first_pass(string flnm);
bool second_pass(string flnm);
Symtab symtab;
bool baseSet;
int baseAddr;

int main(int argc, char* argv[]) {
    if (argc == 1) {
        cout << "Please Input valid SIC/XE filename(s)" << endl;
        return 0;
        string flnm;

    for(int j = 1; j < argc; j++) {
        flnm = argv[j];
        bool ok = first_pass(flnm);
        if (!ok) {
            return 1;
        }
        ok = second_pass(flnm);
        if (!ok) {
            return 1;
        }
    }

    return 0;
}

}

bool first_pass(string flnm) 
{
    fstream sicfile(flnm);
    string line, line2;
    int run_total = 0;
    vector<string> holder;
    string op, operand, csectout;
    char buffer[256];
    std::vector<std::string> outlines;
    std::vector<std::string> outLit;
    
    //create the .l file and a way to add lines to it
    auto pos = flnm.find('.');
    string listing_file = flnm;
    listing_file = listing_file.substr(0, pos);
    listing_file += ".st";
    FILE *fptr = fopen(listing_file.c_str(), "w"); 
    if (fptr == nullptr) 
    { 
        printf("Could not open %s\n", listing_file.c_str()); 
        return 0; 
    }
    fprintf(fptr, "%-8s%-8s%-8s%-8s%-8s\n", "CSect", "Symbol", "Value", "LENGTH", "Flags");
    fprintf(fptr, "--------------------------------------\n");

    //building the tables as long as there's still lines to read in file
    while(std::getline(sicfile, line)) {
        if (line[0] == '.') {
            continue;
        }
        char prefix = 0;
        char preop = 0;
        std::string label = get_label(line);
        std::string op = get_op(line, prefix);
        std::string operand = get_operand(line, preop);
        OpEntry entry = get_OpEntry(op);
        std::string labelout = "";
        Instruction instruct(run_total, line);


        if (label.size() > 0) {
            symtab.values[label] = run_total;
            labelout = label;
            
        }
        
        //If not literal, add to the first table, else add to second table
        if (labelout != "*") {
            symtab.flags[labelout] = "R";
            //print labels to SYMTAB
            if (!labelout.empty() && labelout != "*") {
                sprintf(buffer, "%-8s%-8s%06X%-10s%-8s\n", "", labelout.c_str(), run_total, "", symtab.flags[labelout].c_str());
                outlines.push_back(buffer);
            }
        } else {
            op.erase(op.begin());
            for (int i = 0; i < op.size(); i++) {
                if (op[i] < 'A' || op[i] > 'Z' && op[i] < 'a'|| op[i] > 'z') {
                    op.erase(i, 1);
                }
            unsigned long litValue = 0;
            unsigned long length = 0;
            std::string currOp;

            //generate correct littab values
            findLitValue(op, currOp, litValue, length);

            //set address correctly
            symtab.values[op] = symtab.values["*"];
            symtab.flags[op] = "A";

            //print literal to LITTAB
            sprintf(buffer, "%-8s%-8lX%-8X%-8lu\n", currOp.c_str(), litValue, run_total, length);
            run_total += length;
            outLit.push_back(buffer);
        }
        }
        
        //figure out how many bytes we need for each line
        if (entry.codename == op){
           run_total += entry.form;
        } else {
            AddrEntry entry = get_AddrEntry(op);
            if (entry.codename == "START") {
                csectout = labelout;
                run_total = 0;
            } else if (entry.codename == "END") {
                run_total += 3;
            } else if (entry.codename == "BYTE") {
                run_total += 1;
            } else if (entry.codename == "WORD") {
                run_total += 2;
            } else if (entry.codename == "RESB") {
                run_total += stoi(operand);
            } else if (entry.codename == "RESW") {
                run_total += 3*stoi(operand);
            } 
            
        }

    
    }
    sprintf(buffer, "%-8s%-8s%-8s%06X%-8s\n", csectout.c_str(), "", "", run_total, "");
    outlines[0] = buffer; 
    for (auto s:outlines ) {
        fprintf(fptr, "%s", s.c_str());
    }

    fprintf(fptr, "\n");
    fprintf(fptr, "Literal Table\n");
    fprintf(fptr, "%-8s%-8s%-8s%-8s\n", "Name", "Operand", "Address", "Length:");
    fprintf(fptr, "--------------------------------\n");
    for (auto s:outLit ) {
        fprintf(fptr, "%s", s.c_str());
    }

    return true;
}

bool second_pass(string flnm) 
{
    fstream sicfile(flnm);
    string line, line2;
    vector<string> holder;
    string op, operand;
    char buffer[256];
    std::vector<std::string> outl2;
    int run_total = 0;
    bool foundEnd = false;

    while((std::getline(sicfile, line)) && !foundEnd) {
        if (line[0] == '.') {
            continue;
            sprintf(buffer, "%s\n", line.c_str());
            outl2.push_back(buffer);
        }

        char prefix = 0;
        char preop = 0;
        std::string label = get_label(line);
        std::string op = get_op(line, prefix);
        std::string operand = get_operand(line, preop);
        OpEntry entry = get_OpEntry(op);
        std::string labelout, operout = "";
        Instruction instruct(run_total, line);
        std::string prefixString(1, instruct.prefix);
        std::string preopString(1, instruct.preop);

        if (entry.codename != op) {
            AddrEntry entry = get_AddrEntry(op);
            if(label == "*") {
                unsigned long litValue = 0;
                unsigned long length = 0;
                std::string currOp;
                findLitValue(op, currOp, litValue, length);
                sprintf(buffer, "%04X%4s%-7s%-1s%-8s%-14s%4s%lX\n", run_total, " ", get_label(line).c_str(), prefixString.c_str(), instruct.op.c_str(), instruct.operand.c_str(), "", litValue);
                run_total += length;
            }
            else if (entry.codename == "END") {
                sprintf(buffer, "%4s%4s%-8s%-8s%-8s%4s%s\n", "", " ", get_label(line).c_str(), instruct.op.c_str(),
                        instruct.operand.c_str(), "", instruct.get_instform().c_str());
                foundEnd = true;
            }
            else {
                sprintf(buffer, "%04X%4s%-7s%-1s%-8s%-8s%4s%s\n", run_total, " ", get_label(line).c_str(), prefixString.c_str(), instruct.op.c_str(), instruct.operand.c_str(), "", instruct.get_instform().c_str());
            }
        }
        else {
            sprintf(buffer, "%04X%4s%-7s%-1s%-7s%-1s%-14s%4s%s\n", run_total, " ", get_label(line).c_str(), prefixString.c_str(), instruct.op.c_str(), preopString.c_str(), instruct.operand.c_str(), "", replaceUppercase(instruct.get_instform()).c_str());
        }

        if (label.size() > 0) {
            symtab.values[label] = run_total;
        }
        if (entry.codename == op){
           run_total += entry.form;
        } else {
            AddrEntry entry = get_AddrEntry(op);
            if (entry.codename == "START") {
                run_total = 0;
            } else if (entry.codename == "END") {
                run_total += 3;
            } else if (entry.codename == "BYTE") {
                run_total += 1;
            } else if (entry.codename == "WORD") {
                run_total += 2;
            } else if (entry.codename == "RESB") {
                run_total += stoi(operand);
            } else if (entry.codename == "RESW") {
                run_total += 3*stoi(operand);
            } else if (entry.codename == "BASE") {
                baseSet = true;
                baseAddr = findValue(operand, symtab);
            } else if (entry.codename == "NOBASE") {
                baseSet = false;
            }
            
        }
        
        if (prefix > 1) {
            sprintf(buffer, "%04x%04s%-8s%01c%-8s%-8s%04s%s\n", run_total, " ",  get_label(line).c_str(), instruct.prefix, instruct.op.c_str(), instruct.operand.c_str(), "", instruct.get_instform().c_str());
        } else {
            sprintf(buffer, "%04x%04s%-9s%-8s%-8s%04s%s\n", run_total, " ", get_label(line).c_str(), instruct.op.c_str(), instruct.operand.c_str(), "", instruct.get_instform().c_str());
        }

        outl2.push_back(buffer);
        if (instruct.op == "END") {
            break;
        }
    }

    auto pos = flnm.find('.');
    string listing_file = flnm;
    listing_file = listing_file.substr(0, pos);
    listing_file += ".l";
    FILE *fptr = fopen(listing_file.c_str(), "w"); 
    if (fptr == NULL) 
    { 
        printf("Could not open %s\n", listing_file.c_str()); 
        return 0; 
    }

    for (auto s:outl2) {
        fprintf(fptr, "%s", s.c_str());
    }
    
    return true;
}


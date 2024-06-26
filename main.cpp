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


bool first_pass(Symtab & symtab, string flnm);
bool second_pass(Symtab & symtab, string flnm);
Symtab symtab;
bool baseSet;
int baseAddr;

int main(/*  int argc, char const * argv[]  */) {

    /* std::vector<std::string> files;
    int filecounter = 0; */

    /* for (auto s:files) {
        string flnm = files[filecounter];

        bool ok = first_pass(symtab, flnm);
        if(!ok) {
            return 1;
        }
        ok = second_pass(symtab, flnm);
        if(!ok) {
            return 1;
        }
        filecounter+=1;
    } */
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
    fstream sicfile(flnm);
    string line, line2;
    int run_total = 0;
    vector<string> holder;
    string op, operand;
    char buffer[256];
    std::vector<std::string> outlines;
    std::vector<std::string> outLit;
    
    //create the .l file and a way to add lines to it
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
        OpEntry entry = get_OpEntry(op, prefix);
        std::string labelout, csectout = "";
        Instruction instruct(line);

        if (label.size() > 0) {
            symtab.values[label] = run_total;
            labelout = label;
            
        }
        
        //If not literal, add to the first table, else add to second table
        if (labelout != "*") {
            if (labelout != "" && labelout != "*") {
                sprintf(buffer, "%-8s%-8s%06x%10s%-8s\n", csectout.c_str(), labelout.c_str(), run_total, "", "F");
                outlines.push_back(buffer);
            }
        } else {
            op.erase(op.begin());
            for (int i = 0; i < op.size(); i++) {
                if (op[i] < 'A' || op[i] > 'Z' && op[i] < 'a'|| op[i] > 'z') {
                    op.erase(i, 1);
                }
        }
            sprintf(buffer, "%-8s%-8s%06x%02s%-8i\n", op.c_str(), instruct.get_instform().c_str(), run_total, "", entry.form);
            outLit.push_back(buffer);
        }
        
        //figure out how many bytes we need for each line
        if (entry.codename == op){
           run_total += entry.form;
        } else {
            AddrEntry entry = get_AddrEntry(op, prefix);
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
            } 
            
        }

    
    }
    sprintf(buffer, "%-8s%-8s%-8s%06x%-8s\n", "SUM", "", "", run_total, "");
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

bool second_pass(Symtab & /*symtab*/, string flnm) 
{
    fstream sicfile(flnm);
    // TODO: open file
    string line, line2;
    vector<string> holder;
    string op, operand;
    char buffer[256];
    std::vector<std::string> outl2;
    int run_total = 0;
    
    // TODO: Keep track of line number to pass to instruction
    while(std::getline(sicfile, line)) {
        if (line[0] == '.') {
            continue;
        }

        char prefix = 0;
        char preop = 0;
        std::string label = get_label(line);
        std::string op = get_op(line, prefix);
        std::string operand = get_operand(line, preop);
        OpEntry entry = get_OpEntry(op, prefix);
        std::string labelout, operout = "";
        Instruction instruct(line);
        if (label.size() > 0) {
            symtab.values[label] = run_total;
        }
        if (entry.codename == op){
           run_total += entry.form;
        } else {
            AddrEntry entry = get_AddrEntry(op, prefix);
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
    listing_file += ".st";
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


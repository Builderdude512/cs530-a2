// Your First C++ Program

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
    char buffer[256];
    std::vector<std::string> outlines;
    std::vector<std::string> outLit;
    
    //TODO build a p2sample.l filename from flnm
    /* std::filesystem::path listing_file{sicfile}, ext{"sic"};
    listing_file.replace_extension(ext); */
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

        if (label.size() > 0) {
            symtab.values[label] = run_total;
            labelout = label;
            
        }
        
        if (labelout != "*") {
            if (labelout != "" && labelout != "*") {
                sprintf(buffer, "%-8s%-8s%06x%-8s%-8s\n", csectout.c_str(), labelout.c_str(), run_total, "", "F");
                outlines.push_back(buffer);
            }
        } else {
            std::string holder = prefix + op;
            sprintf(buffer, "%-8s%-8s%06x%-8i\n", holder.c_str(), "", run_total, entry.form);
            outLit.push_back(buffer);
        }
        /* out << entry.codename <<  " " << entry.form << " ";
        cout << "label = " << label << " " << std::hex << run_total << "\n";  */
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
    printf("second\n") ;
    std::cout << flnm << std::endl;
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
        std::string labelout, csectout = "";
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

        sprintf(buffer, "%06x%-8s%-8s%-8s%-8s\n", run_total, get_label(line).c_str(), instruct.op.c_str(), instruct.operand.c_str(), "");
        outl2.push_back(buffer);
    }

    for (auto s:outl2 ) {
        cout << s;
    }
    
    return true;
}


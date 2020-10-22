#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "PIF.h"
#include "SymbolTable.h"
//b). 2 symbol tables
using namespace std;
static inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
}
int main() {
    SymbolTable * identifiers = new SymbolTable();
    SymbolTable * constants = new SymbolTable();
    PIF pif;

    ifstream fin("prog.txt");
    int count = 1;
    char line[100];
    while (fin.getline(line, 100)) {
        char * token = strtok(line, " ");
        while(token != nullptr) {
            string t {token};
            ltrim(t);
            if (!pif.detect(token, identifiers, constants)){
                cout<<"LEXICAL_ERROR_FOUND_AT_LINE: " << count << " INVALID TOKEN: " << t << endl;
            };
            token = strtok(NULL, " ");
        }
        count++;
    }
    fin.close();
    return 0;
}

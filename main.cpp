#include <string>
#include <fstream>
#include "PIF.h"
#include "SymbolTable.h"
#include "scanner.h"

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
        string s {line};
        spacearize(s);
        ltrim(s);

        char * lineAsChar = const_cast<char*>(s.c_str());
        char * token = strtok(lineAsChar, " ");
        while(token != nullptr) {
            bool isOkay = false;
            if(isReservedWord(token)) {
                isOkay = true;
                pif.insertToken(token, 0);
            }
            if(isSeparator(token)) {
                isOkay = true;
                pif.insertToken(token, 0);

            }
            if(isOperator(token)) {
                isOkay = true;
                pif.insertToken(token, 0);

            }
            if(isConstant(token)) {
                isOkay = true;
                int index = constants->pos(token);
                pif.insertToken(token, index);

            }
            if(isIdentifier(token)) {
                isOkay = true;
                int index = identifiers->pos(token);
                pif.insertToken(token, index);
            }
            if(!isOkay) {
                cout<<"LEXICAL ERROR AT LINE: " << count << " UNRECOGNIZED TOKEN " << token << endl;
            }
            token = strtok(NULL, " ");
        }
        count++;
    }
    fin.close();
    return 0;
}

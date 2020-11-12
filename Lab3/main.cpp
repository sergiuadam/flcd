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

void readReservedWords() {
    ifstream fin("tokens.txt");
    string buffer;
    char line[100];
    while(fin.getline(line, 100)){
        if(line[strlen(line)-1] == '\r') {
            line[strlen(line)-1] = '\0';
        }
        reservedWords.emplace_back(string{line});
    }
}
int main(int argc, char** argv) {
    readReservedWords();
    SymbolTable * identifiers = new SymbolTable();
    SymbolTable * constants = new SymbolTable();
    PIF pif;

    ifstream fin(argv[1]);
    int count = 1;
    char line[100];
    while (fin.getline(line, 100)) {
        string s {line};
        spacearize(s);
        ltrim(s);
        char * lineAsChar = const_cast<char*>(s.c_str());
        char * token = strtok(lineAsChar, " ");
        while(token != nullptr) {
            if(token[strlen(token)-1] == '\r') {
                token[strlen(token)-1] = token[strlen(token)];
            }
            bool isOkay = false;
            if(isReservedWord(token) && !isOkay) {
                isOkay = true;
                pif.insertToken(token, 0);
            }
            if(isSeparator(token) && !isOkay) {
                isOkay = true;
                pif.insertToken(token, 0);

            }
            if(isOperator(token) && !isOkay) {
                isOkay = true;
                pif.insertToken(token, 0);

            }
            if(isConstant(token) && !isOkay) {
                isOkay = true;
                int index = constants->pos(token);
                pif.insertToken("_constant", index);

            }
            if(isIdentifier(token) && !isOkay) {
                isOkay = true;
                int index = identifiers->pos(token);
                pif.insertToken("_identifier", index);
            }
            if(!isOkay) {
                cout<<"LEXICAL ERROR AT LINE: " << count << " UNRECOGNIZED TOKEN " << token << endl;
            }
            token = strtok(NULL, " ");
        }
        count++;
    }
    fin.close();

    //OUTPUT
    ofstream fpif("pif.out");
    for(auto pereche : pif.all) {
        fpif<<pereche.first<<" "<<pereche.second<<endl;
    }
    fpif.close();

    ofstream fsymbol("symbol.out");
    for(auto entry : constants->table) {
        Node * e = entry;
        while(e != nullptr) {
            fsymbol<<e->identifier<<" "<<e->index<<endl;
            e = e->next;
        }
    }
    for(auto entry : identifiers->table) {
        Node * e = entry;
        while(e != nullptr) {
            fsymbol<<e->identifier<<" "<<e->index<<endl;
            e = e->next;
        }
    }
    fsymbol.close();
    return 0;
}

#pragma once
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

<<<<<<< HEAD:main.cpp
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
=======
struct Node {
    string identifier;
    int index;
    Node * previous = nullptr;
    Node * next = nullptr;
};

class SymbolTable {
public:
    vector<Node *> table;

    int hash(string identifier) {
        unsigned long sum = 0;
        for(int i = 0; i < identifier.length(); i++) {
            sum += static_cast<int>(identifier[i]);
        }
        return sum % 67;
    }

    SymbolTable() {
        for(int i = 0; i < 67; i++) {
            table.push_back(nullptr);
        }
    }

    int search(string identifier) {
        int pos = hash(identifier);
        if(table[pos] == nullptr) {
            return -1;
        }
        Node * firstNode = table[pos];
        while (firstNode->next != nullptr) {
            if(firstNode->identifier == identifier) {
                return firstNode->index;
            }
        }
        return -1;
    }

    int insert(string identifier) {
        int pos = hash(identifier);
        if(table[pos] == nullptr) {
            table[pos] = new Node{identifier, 0, nullptr, nullptr};
            return 0;
        }
        Node * firstNode = table[pos];
        while (firstNode->next != nullptr) {
            if(firstNode->identifier == identifier) {
                return firstNode->index;
            }
            firstNode = firstNode->next;
        }
        firstNode->next = new Node{identifier, firstNode->index + 1, firstNode, nullptr};
        return firstNode->index + 1;
    }
    int pos(string token) {
        int searchResult = search(token);
        if (searchResult == -1) {
            return insert(token);
        } else {
            return searchResult;
        }
    }
};
>>>>>>> lab3:Lab3/SymbolTable.h

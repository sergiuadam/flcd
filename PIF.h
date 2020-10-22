#pragma once
#include <vector>
#include "SymbolTable.h"

using namespace std;

class PIF {
public:

    vector<pair<string, int>> all;
    bool detect(string token, SymbolTable * identifiers, SymbolTable * constants);

    bool isReservedWord(string token);

    bool isConstant(string token);

    bool isSeparator(string token);

    bool isOperator(string token);

    bool isIdentifier(string token);

    bool checkStrings(const string &token, vector<string>) const;
};

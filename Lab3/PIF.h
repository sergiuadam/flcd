#pragma once
#include <vector>
#include "SymbolTable.h"

using namespace std;

class PIF {
public:
    vector<pair<string, int>> all;
    void insertToken(string token, int pos);
};

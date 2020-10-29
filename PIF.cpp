//
// Created by loco on 22/10/2020.
//

#include "PIF.h"
#include <string>
#include <regex>
#include <iostream>
using namespace std;

void PIF::insertToken(string token, int pos) {
    all.emplace_back(pair<string, int>{token, pos});
}



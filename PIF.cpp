//
// Created by loco on 22/10/2020.
//

#include "PIF.h"
#include <string>
#include <regex>
#include <iostream>
using namespace std;

bool PIF::detect(string token, SymbolTable * identifiers, SymbolTable * constants) {
    if (isReservedWord(token)) {
        all.push_back(pair<string, int>{token, 0});
        return true;
    }

    if(isSeparator(token)) {
        all.push_back(pair<string, int>{token, 0});
        return true;
    }
    if(isOperator(token)) {
        all.push_back(pair<string, int>{token, 0});
        return true;
    }

    if(isConstant(token)) {
        int index = constants->pos(token);
        all.push_back(pair<string, int>{token, index});
        return true;
    }

    int index = identifiers->pos(token);
    all.push_back(pair<string, int>{token, index});
    return true;
}

bool PIF::checkStrings(const string &token, vector<string> givenFilter) const {
    bool isOkay = false;

    for(auto s : givenFilter) {
        if(token.compare(s) == 0){
            isOkay = true;
        };
    }
    return isOkay;
}

bool PIF::isReservedWord(string token) {
    vector<string> reservedWords = {"INTREG",
                            "CARACTER",
                            "INTERVAL",
                            "ADEVAR",
                            "ADEVARAT",
                            "MINCIUNA",
                            "BAGA",
                            "READ_FROM_USER",
                            "PRINT_TO_USER",
                            "DECLAR",
                            "DACA",
                            "ATUNCI",
                            "INCEPE_SMECHERIA",
                            "GATA_SMECHERIA",
                            "TARE",
                            "DEFINITIE"};
    return checkStrings(token, reservedWords);

}

bool PIF::isConstant(string token) {
    std::regex cifre("^[0-9]*$",
                          std::regex_constants::ECMAScript | std::regex_constants::icase);
    std::regex string("^");
    if (std::regex_search(token, cifre)) {
        return true;
    }
    return false;
}

bool PIF::isSeparator(string token) {
    vector<string> separators = {",",
                                 ";",
                                 "(",
                                 ")",
                                 "{",
                                 "}",
                                 "[",
                                 "]"};
    return checkStrings(token, separators);
}

bool PIF::isOperator(string token) {
    vector<string> operators = {"<", "<=", "==", ">=", "+", "-", "/", "*", "%"};
    return checkStrings(token, operators);
}

bool PIF::isIdentifier(string token) {

}

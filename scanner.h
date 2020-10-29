//
// Created by loco on 22/10/2020.
//
#pragma once
#include <string>
#include <regex>
#include <iostream>
using namespace std;
vector<string> separators = {",", ";", "(", ")", "{", "}", "[", "]"};
vector<string> operators = {"<=", ">=", "<", ">", "=", "+", "-", "/", "*", "%"};
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
enum Type{
    resW, oper, sep
};
bool checkStrings(const string &token, Type t)  {
    bool isOkay = false;
    vector<string> givenFilter;
    switch (t) {
        case 0: givenFilter = reservedWords; break;
        case 1: givenFilter = operators; break;
        case 2: givenFilter = separators; break;
    }
    for(auto s : givenFilter) {
        if(token.compare(s) == 0){
            isOkay = true;
        };
    }
    return isOkay;
}

bool isConstant(string token) {
    std::regex cifre("^[0-9]*$", std::regex_constants::ECMAScript | std::regex_constants::icase);
    std::regex caractereString("^(?:\".*\"$)$", std::regex_constants::ECMAScript | std::regex_constants::icase);

    if (std::regex_search(token, cifre)) {
        return true;
    }
    if(std::regex_search(token, caractereString)) {
        return true;
    }
    return false;
}

bool isSeparator(string token) {
    return checkStrings(token, sep);
}

bool isOperator(string token) {
    return checkStrings(token, oper);
}

bool isReservedWord(string token) {
    return checkStrings(token, resW);
}

bool isIdentifier(string token) {
    std::regex word("^\\w+$", std::regex_constants::ECMAScript | std::regex_constants::icase);
    std::regex cifre("^[0-9]*$", std::regex_constants::ECMAScript | std::regex_constants::icase);
    if(regex_search(token, word)) {
        if (regex_search(string{token[0]}, cifre)){
            return false;
        }
        return true;
    }
    return false;
}

bool spacearize(string& s) {
    //This function puts assures that there is exactly one space before AND after each separator / operator.
    for(int i = 0; i < s.size(); i++) {
        if(isSeparator(string{s[i]})) {
            if(!isspace(s[i + 1])) {
                s.insert(i + 1, " ");
            }
            if(!isspace(s[i - 1])) {
                s.insert(i, " ");
            }
            i++;
        }
        else {
            if (isOperator(string{s[i]})) {
                if(isOperator(string{s[i + 1]})) {
                    bool ok = true;
                    if(!isspace(s[i + 2])) {
                        s.insert(i + 2, " ");
                    }
                    if(!isspace(s[i - 1])) {
                        s.insert(i, " ");
                    }
                    i+=2;
                }
                else {
                    if(!isspace(s[i + 1])) {
                        s.insert(i + 1, " ");
                    }
                    if(!isspace(s[i - 1])) {
                        s.insert(i, " ");
                    }
                    i++;
                }
            }
        }
    }
}
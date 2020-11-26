#pragma once
#include <vector>
#include <string>
#include <map>
using namespace std;
struct TransitionFunction {
    string s1;
    string s2;
    string s3;
};

class FiniteAutomata {
    vector<string> states;
    vector<string> alphabet;
    vector<string> initialState;
    vector<string> finalStates;
    vector<TransitionFunction> transitionFunctions;
public:
    FiniteAutomata() {transitionFunctions.reserve(10);}
    void readFromFile(char * fileName);
    void printStates();
    void printAlphabet();
    void printInitialState();
    void printFinalStates();
    void printTransitionFunctions();
    void checkSequence();
    string getNextState(string currentState, string a);
};

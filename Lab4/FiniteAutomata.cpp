#include <fstream>
#include <iostream>
#include "FiniteAutomata.h"

void FiniteAutomata::readFromFile(char * fileName) {
    ifstream fin(fileName);
    string line;
    int i = -1;
    while(getline(fin, line)) {
        i++;
        if(i == 0) {
            int pos = 0;
            while ((pos = line.find(",")) != std::string::npos) {
                states.emplace_back(string{line.substr(0, pos)});
                line.erase(0, pos + 1);
            }
            states.emplace_back(string{line});
        }
        if(i == 1) {
            int pos = 0;
            while ((pos = line.find(",")) != std::string::npos) {
                alphabet.emplace_back(string{line.substr(0, pos)});
                line.erase(0, pos + 1);
            }
            alphabet.emplace_back(string{line});
        }
        if(i == 2) {
            int pos = 0;
            while ((pos = line.find(",")) != std::string::npos) {
                initialState.emplace_back(string{line.substr(0, pos)});
                line.erase(0, pos + 1);
            }
            initialState.emplace_back(string{line});
        }
        if(i == 3) {
            int pos = 0;
            while ((pos = line.find(",")) != std::string::npos) {
                finalStates.emplace_back(string{line.substr(0, pos)});
                line.erase(0, pos + 1);
            }
            finalStates.emplace_back(string{line});
        }
        if(i > 3) {
            TransitionFunction t1;
            int pos = 0;
            int ind = 0;
            while ((pos = line.find(",")) != std::string::npos) {
                if(ind == 0) {
                    t1.s1 = string{line.substr(0, pos)};
                }
                if(ind == 1) {
                    t1.s2 = string{line.substr(0, pos)};
                }
                ind++;
                line.erase(0, pos + 1);
            }
            t1.s3 = string{line};
            transitionFunctions.emplace_back(t1);
        }
    }
}
void FiniteAutomata::printStates() {
    cout<<"States: ";
    for(auto state : states) {
        cout<<state<<" ";
    }
    cout<<endl;
}

void FiniteAutomata::printAlphabet() {
    cout<<"Alphabet: ";
    for(auto alpha : alphabet) {
        cout<<alpha<<" ";
    }
    cout<<endl;
}

void FiniteAutomata::printInitialState() {
    cout<<"Initial State: ";
    for(auto state : initialState) {
        cout<<state<<" ";
    }
    cout<<endl;
}

void FiniteAutomata::printFinalStates() {
    cout<<"Final States: ";
    for(auto state : finalStates) {
        cout<<state<<" ";
    }
    cout<<endl;
}

void FiniteAutomata::printTransitionFunctions() {
    cout<<"TransitionFunctions: ";
    for(auto fnc : transitionFunctions) {
        cout<<fnc.s1<<" "<<fnc.s2<<" "<<fnc.s3<<"; ";
    }
    cout<<endl;
}

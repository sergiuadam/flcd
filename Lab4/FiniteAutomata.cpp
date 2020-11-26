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

void FiniteAutomata::checkSequence() {
    ifstream fin("../seq.in");
    vector<string> operations;
    string line;
    int i = -1;
    while(getline(fin, line)) {
        i++;
        if (i == 0) {
            int pos = 0;
            while ((pos = line.find(" ")) != std::string::npos) {
                operations.emplace_back(string{line.substr(0, pos)});
                line.erase(0, pos + 1);
            }
            operations.emplace_back(string{line});
        }
    }
    map<string, pair<string, string>> cs;
    bool isDFA = true;
    string current = states.front();
    for(int i = 0; i < operations.size();) {
        if (cs.contains(current)) {
            if(cs[current].first == operations[i]) {
                if (cs[current].second != getNextState(current, operations[i])) {
                    isDFA = false;
                    break;
                }
            }
        } else {
            string nextState = getNextState(current, operations[i]);
            if(nextState.size() == 0) {
                isDFA = false;
                break;
            }
            cs[current] = pair<string, string>{operations[i], nextState};
            current = nextState;
        }

        i++;
        if(i == operations.size()) {
            //We reached the end of the sequence, so we verify if the current state is amongst final states
            bool ok = false;
            for(auto state : finalStates) {
                if(state == current) {
                    ok = true;
                    break;
                }
            }
            isDFA = ok;
            break;
        }
    }
    cout<<"Print 1 if sequence is accepted. Print 0 otherwise"<<endl;
    cout<<isDFA;
}

string FiniteAutomata::getNextState(string currentState, string a) {
    for(auto func : transitionFunctions) {
        if(func.s1 == currentState && func.s2 == a) {
            return func.s3;
        }
    }
    return string{};
}

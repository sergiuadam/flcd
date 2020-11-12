#include <iostream>
#include "FiniteAutomata.h"
#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
using namespace std;

int main() {
    FiniteAutomata a;
    a.readFromFile("../fa.in");
    cout<<"1.Print states"<<endl;
    cout<<"2.Print alphabet"<<endl;
    cout<<"3.Print initial state"<<endl;
    cout<<"4.Print final states"<<endl;
    cout<<"5.Print transition functions"<<endl;
    cout<<"6.Check sequence"<<endl;
    bool ok = true;
    while (ok) {
        int i;
        cin>>i;
        switch (i) {
            case 1 : a.printStates(); break;
            case 2 : a.printAlphabet(); break;
            case 3 : a.printInitialState(); break;
            case 4 : a.printFinalStates(); break;
            case 5 : a.printTransitionFunctions(); break;
            case 6 : a.checkSequence(); break;
            default : ok = false; break;
        }
    }
}

#pragma clang diagnostic pop
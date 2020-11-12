#include <iostream>
#include "FiniteAutomata.h"
using namespace std;

int main() {
    FiniteAutomata a;
    a.readFromFile("../fa.in");
    cout<<"1.Print states"<<endl;
    cout<<"2.Print alphabet"<<endl;
    cout<<"3.Print initial state"<<endl;
    cout<<"4.Print final states"<<endl;
    cout<<"5.Print transition functions"<<endl;
    while (true) {
        int i;
        cin>>i;
        switch (i) {
            case 1 : a.printStates(); break;
            case 2 : a.printAlphabet(); break;
            case 3 : a.printInitialState(); break;
            case 4 : a.printFinalStates(); break;
            case 5 : a.printTransitionFunctions(); break;
            default : cout<<"Invalid input given"<<endl; break;
        }
    }
}

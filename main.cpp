#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Node {
    string identifier;
    int index;
    Node * previous = nullptr;
    Node * next = nullptr;
};

struct SymbolTable {
    vector<Node *> table;
    SymbolTable() {
        for(int i = 0; i < 67; i++) {
            table.push_back(nullptr);
        }
    }

    int hash(string identifier) {
        unsigned long sum = 0;
        for(int i = 0; i < identifier.length(); i++) {
            sum += static_cast<int>(identifier[i]);
        }
        return sum % 67;
    }

    int insert(string identifier) {
        int pos = hash(identifier);
        if(table[pos] == nullptr) {
            table[pos] = new Node{identifier, 0, nullptr, nullptr};
            return 0;
        }
        Node * firstNode = table[pos];
        while (firstNode->next != nullptr) {
            if(firstNode->identifier == identifier) {
                return firstNode->index;
            }
            firstNode = firstNode->next;
        }
        firstNode->next = new Node{identifier, firstNode->index + 1, firstNode, nullptr};
        return firstNode->index + 1;
    }

    int search(string identifier) {
        int pos = hash(identifier);
        if(table[pos] == nullptr) {
            return -1;
        }
        Node * firstNode = table[pos];
        while (firstNode->next != nullptr) {
            if(firstNode->identifier == identifier) {
                return firstNode->index;
            }
        }
        return -1;
    }
};
//It is written like this in order to strictly respect Course 2's declaration.
int pos (string token, SymbolTable& symbolTable) {
    int searchResult = symbolTable.search(token);
    if (searchResult == -1) {
        return symbolTable.insert(token);
    }
    else {
        return searchResult;
    }
}
int main() {
    return 0;
}

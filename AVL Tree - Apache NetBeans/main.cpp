#include <cstdlib>
#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <random>
#include "LinkedList.h"
#include "AVL.h"

using namespace std;

//GLOBAL CONSTANTS
const int SIZE = 512;
const std::vector<int> ABCtoNum = {2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5, 6, 6, 6, 7, 7, 7, 7, 8, 8, 8, 9, 9, 9, 9};


//FUNCTION DECLARATION
int hashFunc(const string);
string createInitials(int);
void mainProgram();
void printTree(AVL, vector<int>);

int main() {
    //RANDOM SEED
    srand(time(NULL));
    
    //IN SCOPE CONSTANTS
    const int initialLength = 3;
    
    //INITIALIZE A BINARY TREE
    AVL AVLTree;
    
    //INITIALIZE A HASH-TABLE
    vector<list<string>> HashTable(SIZE);

    //FILL THE HASH-TABLE AND THE BINARY TREE WITH 512 RANDOM 3 LETTER INITIALS
    for(int i = 0; i < SIZE; ++i) {
        std::string initials = createInitials(initialLength); //CREATE THE RANDOM 3 LETTER INITIAL
        int hash = hashFunc(initials); //HASH IT (TURN THE 3 LETTER INITIALS INTO AN INTEGER VALUE)
        
        HashTable[hash].push_back(initials); // STORE IT IN THE HASH TABLE
        AVLTree.AddLeaf(hash); // STORE IT IN THE BINARY TREE
    }
    
    //STATISTICALS
    LinkedList linkedList(SIZE);
    for (const auto& link : HashTable) {
        int size = link.size();
        linkedList[size]++;
    }

    cout << "Traversing the Hash Table\n";
    linkedList.printCollisions(12);
 
    
    cout << "\n\nTraversing the AVL Tree\n";
    AVLTree.PrintCollisions(12);
    //AVLTree.PrintTree2D(10);

    return 0;
}

void printTree(AVL tree, vector<int> data){
    for(const auto& node : data){
        tree.PrintChildren(node);
        cout << "\n";
    }
    //cout << "size "  << data.size();
}

int hashFunc(const string key){
    int hash{};
    
    int indx = 1;
    for(char letters : key){
        int valOfLetter = ABCtoNum[letters - 'A']; //CALCULATE WHAT VALUE THIS LETTER HAS BASED ON IT'S TELEPHONE NUMBER VALUE
        hash = hash * 10 + valOfLetter;
        hash += key[indx];
        
        indx++;
    }
    
    return hash % SIZE; //RETURN THE HASH
}

string createInitials(int length){
    const int numInABC = 26;
    std::string letters = "";
    
    for(int i = 0; i < length; i++){ letters += static_cast<char>('A' + rand() % numInABC); }
    return letters;
}


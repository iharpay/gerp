/*
HashTable.h
April 30
Joshua Bernstein and Ayah Harper
File purpose: The purpose of this file
is to initialize our hashTable methods. 
under the hood, the hash table is implemented
as a vector. This file again serves a greater
purpose in our program by allowing us to store
data and retrieve it in O(1) time. 

*/
#ifndef HASH_TABLE_H
#define HASH_TABLE_H
#include <string>
#include <iostream>
#include <list>
#include <vector>

#include "Word.h"

using namespace std;

class HashTable{

    public:
    // Public Constructor
    HashTable();

    // Destructor
    ~HashTable();

    void hashIn(Word word_struct);

    bool hashOut(vector <string> filePaths, string &wordToFind, 
    ostream &outfile, bool noCase);

    int size();

    void toString();
   
    private:
    
    // under the hood, the hash table is implemented using
    // chaining as a vector of lists of word structs
    vector <list<Word>> table;

    // resizing + rehashing function
    void re_up();

    list <Word>::iterator it; 

    // private variables to monitor load factor
    int tableSize;
    int numElements;

   
};

#endif

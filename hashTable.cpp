/*
HashTable.cpp
April 30
Joshua Bernstein and Ayah Harper
File purpose: The purpose of this file
is to create and implement a hash table
in order to reach O(1) time complexity
in retrieving stored data from files
we got in gerp.cpp. This file plays a bigger
role in our program by creating a hashtable which
allows our program to run in specific time constraints
given hash table's O(1) time complexity!
*/

#include  <string.h>
#include <functional>
#include <sstream>

#include "HashTable.h"
#include "stringProcessing.h"

using namespace std;

/*
HashTable
Input: A size of the hash table
Purpose: Initializes and creates a hash
table of a fixed size
Output: A created hashtable
*/
HashTable::HashTable(){ 
    numElements = 0;  
    tableSize = 100;
    table.resize(tableSize);
}

/*
Input: NOne
Purpose: Destructs out hashtable
Output: NONE
*/
HashTable::~HashTable() {

    int size = table.size();
    for (int i = 0; i < size; i++) {
        table[i].clear();
    }
}

/*
Add
Input: A word to input into the hashtable
Purpose: Adds a word to the hashtable
Output: Void
*/
void HashTable::hashIn(Word word_struct){
    
    // Index for hash table
    int indexed = hash<string>{}(word_struct.low_word) % tableSize;
    table[indexed].push_back(word_struct);
    numElements++; // increment the numElements count

    // LOAD FACTOR CHECK
    if (numElements/tableSize > 0.75) {
        re_up();
    }
}
/* re_up
Input: NONE
Purpose: This creates a new table 
for our hash table in order to maintain a .75 
load factor. This also rehashes words based
on the new table size. 
Output: Void
 */
void HashTable::re_up() {

    // COMPUTE THE NEW TABLE SIZE TO MAINTIAN LOAD FACTOR
    int newSize = 2 * tableSize;
    vector <list<Word>> new_table;
    new_table.resize(newSize);

    // REHASHES BASED ON NEW TABLE SIZE
    for (int i = 0; i < tableSize; i++) {
        if (not table[i].empty()) {
            // Iterate through the lists in the old hash table
            for (it = table[i].begin(); it != table[i].end(); it++) {
                // compute a new index for each list element
                int new_index = hash<string>{}(it->low_word) % newSize;
                new_table[new_index].push_back(*it);

            }

        }
    }

    table = new_table;
    tableSize = newSize;

    return;
}

/*
size
Input: None
Purpose: Get the size of the table
Output: The table size
*/
int HashTable::size(){
    return table.size();
}

/*
TESTING FUNCTION
*/
void HashTable::toString(){
    for (const auto& list : table) {
        for (const auto& word : list) {
            cout << word.raw << "("<< word.lineNumber << "), " ;
        }
        cout << endl;
    }
}


/* hashOut
* purpose: Finds the index of the word in the hashtable
and writes to the output file if the word was found.
* arguments: A vector of strings representing 
each file path. The address of the string of the word
the user puts into the query. An ostream to the address 
of our outputfile. A boolean for whether or not 
the search is case insensitive or not.
* returns: Returns whether or not the word was found 
in the hash table.
* effects:
*/
bool HashTable::hashOut(vector<string> filePaths, string &wordToFind, 
                        ostream &outfile, bool noCase) {
    
    // 1. Convert the argument word to lowercase
    int size = wordToFind.size();
    string lowerWord = "";
    for (int i = 0; i < size; i++) {
        lowerWord += tolower(wordToFind[i]);
    }

    // 2. Compute the index using the lowercase version of 
    // the word
    int index = hash<string>{}(lowerWord) % tableSize;
    
    bool found = false;

    // 3. Iterate through the list at that index to see if the 
    // argument word matches any of the words there
    for(it = table[index].begin(); it !=table[index].end(); it++){
        
        // RAW MATCH (CASE SENSITIVE)
        if (wordToFind == (*it).raw) { 
            found = true; 
            string path = filePaths.at((*it).fileID);
            int line_num = (*it).lineNumber;
            string line_content = (*it).lineContent;
            outfile << path << ":" << line_num << ": "<< line_content << endl;
        } else { // CASE INSENSITIVE MATCH
            if (noCase) { 
                if (lowerWord == (*it).low_word) {
                    found = true;
                    string path = filePaths.at((*it).fileID);
                    int line_num = (*it).lineNumber;
                    string line_content = (*it).lineContent;
                    outfile << path << ":" << line_num << ": "
                    << line_content << endl;
                }
            }
        }
    }

    return found;
    
}

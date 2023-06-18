/* Gerp.cpp
*
* Ayah Harper and Josh Bernstein
* 4/30/2023
* Purpose: This is the implementation of our 
Gerp class. The purpose of this file is simply to 
allow our Gerp object to run. In order to do that,
we have methods in this file to populate 
a file path, to build my index which
lets me store each word and its' 
corresponding word struct. We also 
use this file to take in querys 
and respond to querys. This file plays 
a bigger role in my overall Gerp project
because it allows us to run our Gerp
class and respond to querys etc.
*
*/

#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <set>

#include "Gerp.h"
#include "stringProcessing.h"

using namespace std;

/* default constructor
* purpose: Creates a default instance
of Gerp. 
* arguments: None
* returns: Nothing
* effects: Creates an "empty" or
"basic" version of Gerp class and pushes
a null string to index 0 of our vector
so that we can start our file path at index
1.
*/
Gerp::Gerp(){

    file_paths.push_back("NULL");

}

/* destructor/cleanup
* purpose: Destructor for Gerp-
* arguments: none
* returns: Nothing
* effects: Destructs our file_path
*/
Gerp::~Gerp() {

    file_paths.clear();
}

/* run
* input: root of the file tree that organizes the input
* directory, name of the output file
* purpose: to run Gerp, this function first populates a file
path given the root of the file tree. Then, run builds 
the index of our 
which reads in each word and puts into 
our hash table. Finally, run calls query function
which asks and receives querys to/from the user.
* output: Void
*/
void Gerp::run(DirNode *root, string &outputFile) {

    string name = "";

    populateFilePaths(root, name);

    buildIndex();

    query(outputFile);
    
    return;

}

/* populateFilePaths
* input: pointer to the root of the file tree, string
that stores the path of the file
* purpose: to populate the file_paths vector with the path
of each file in the file tree
* output: none
* effects: go through the file tree, print the path for each
file and store it in the corresponding index in the file_paths
vector
*/
void Gerp::populateFilePaths(DirNode *root, string &prefix) {

    // Base case: If root is null or empty
    if(root==nullptr or root->isEmpty()){
        return;
    }

    // For loop that increments the fileID number and stores the corresponding
    // file path in the vector
    for(int i = 0; i < root->numFiles(); i++){
        file_paths.push_back(prefix + root->getName() + "/" + root->getFile(i));
    }

    // For loop which recursively prints out each subdirectory
    for(int i = 0; i < root->numSubDirs(); i++){
        string subdir_prefix = prefix + root->getName() + "/";
        populateFilePaths(root->getSubDir(i), subdir_prefix);
    }

}


/* buildIndex
* input: None 
* purpose: Reads in each word from each
file and gets rid of duplicate words from
the same line. Then it runs each word
through a hashfuntion and "hashes in" to 
the hash table.
* output: VOID
* effects: Puts each word into the hash table
and updates each word's corresponding
word struct information as well.
*/
void Gerp::buildIndex(){

    int num_files = file_paths.size();

    for(int i = 1; i < num_files; i++) { // FOR LOOP 1: Go through all files
        ifstream infile;
        infile.open(file_paths[i]);

        int line_num = 1; // Initialize line number counter
        string line;

        while (getline(infile, line)) { // WHILE LOOP 1: Get an entire line

            stringstream linestream(line);
            string raw;

            set <string> words_in_line;

            while (linestream >> raw) { // WHILE LOOP 2: Get individual words
               stripNonAlphaNum(raw);
               words_in_line.emplace(raw);
            
            }

            set <string> :: iterator it;

            // FOR LOOP 2: 
            for (it = words_in_line.begin(); it != words_in_line.end(); it++) {

                Word *new_word = new Word;
                new_word->fileID = i;
                new_word->lineNumber = line_num;
                new_word->raw = *it;
                new_word->lineContent = line;

                int size = (*it).size();
                for (int n = 0; n < size; n++) {
                    new_word->low_word += tolower((*it).at(n));
                }

                hashMaster.hashIn(*new_word);
                delete new_word;
            }

            line_num++;
        }

    }

}

/* query
* purpose: Asks and receives queries from/to the user.
* arguments: The output file the user wants to write to
* returns: Void
* effects: Writes to the output file.
*/
void Gerp::query(string &outputFile){
    
    ofstream outfile;
    outfile.open(outputFile);
    cout << "Query? ";
    string query;

    while(cin >> query){

          
        if ((query == "@i") or (query == "@insensitive")) { // CASE INSENSITIVE

            string word;
            cin >> word;

            if (not stripNonAlphaNum(word)) {
                outfile << word << " Not Found." << endl;
            } else {
                if (not hashMaster.hashOut(file_paths, word, outfile, true)) {
                    outfile << word << " Not Found." << endl;
                }
            }
        } 
        else if((query == "@q") or (query == "@quit")) { // QUIT COMMAND
            cout << "Goodbye! Thank you and have a nice day." << endl;
            outfile.close();
            return;
        } 
        else if (query == "@f") { // SWITCHING OUTPUT FILES
            
            outfile.close();
            string newOutFile;
            cin >> newOutFile;
            outfile.open(newOutFile);

        } 
        else { // CASE SENSITIVE SEARCH
            if (not stripNonAlphaNum(query)) {
                outfile << query << " Not Found. Try with "
                << "@insensitive or @i." << endl;
            } else {
                if (not hashMaster.hashOut(file_paths, query, outfile, false)){
                    outfile << query << " Not Found. Try with "
                    << "@insensitive or @i." << endl;
                }
            } 
        }
        
    cout << "Query? ";

    }

    cout << "Goodbye! Thank you and have a nice day." << endl;
    outfile.close();
    return;
    
}

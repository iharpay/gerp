/* Gerp.h
*
* Ayah Harper and Josh Bernstein
* 4/30/2023
* Purpose: This is where we initialize
the methods of my Gerp class. Our Gerp class
and it's purpose/function purposes are explained
in greater detail in my gerp.cpp purpose
in gerp.cpp and overall in the README. But, this file
plays a greater role in my overall program because it
sets up my ability to create an instance of Gerp,
run queries, and index throuhg the hashtabe that we 
created.
* 
*/

#ifndef __GERP_H__
#define __GERP_H__

#include <vector>
#include <list>
#include <iostream>

#include "HashTable.h"
#include "FSTree.h"
#include "DirNode.h"

using namespace std;

class Gerp
{
public:

    Gerp();

    ~Gerp();

    void run(DirNode *root, string &outputFileName);

private:

    vector <string> file_paths;
    
    void populateFilePaths(DirNode *root, string &prefix);

    void buildIndex();

    void query(string &outputFile);

    HashTable hashMaster;
};  

#endif

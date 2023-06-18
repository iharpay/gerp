/* Word.h
* Joshua Bernstein and Ayah Harper
April 30
File purpose: This file holds
our word struct. This holds 
a file id to represent each file,
the word that the struct is assigned to,
the line number the word comes from
along with the contents of the line.
This is assigned to each line we put into
our hash table.
*
*/
#include <iostream>

using namespace std;

struct Word {

    string raw = "";
    string low_word = "";
    int fileID = -1;
    int lineNumber = -1;
    string lineContent = "";

};

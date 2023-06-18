/*
Josh Bernstein and Ayah Harper
4/30
stringProcessing.cpp
File Purpose: The purpose of 
this file is to host a function which 
stripsnon alphanumeric characters
from a given word.
*/
#include <iostream>
#include <string>

using namespace std;

/*
stripNonAlphaNum
Input: An address to a word, 'input'
Purpose: Strip nonAlpaNumeric words 
from a given input
Output: A boolean as to whether or not
at least one alphanumeric char was found
*/
bool stripNonAlphaNum(string &input) {
    
    int first = 0;
    int end = input.size();
    bool good = false; // boolean, indicates that at least one 
                        // alnum char was found

    // Starting from the front, find the index of the first alphanum char
    for (int i = 0; i < end; i++) {
        if (isalnum(input[i])) {
            good = true;
            first = i;
            break;
        }
    }
    
    // Starting from the back, find the index of the last alphanum char
    for (int i = end - 1; i >=first; i--) {
        if (isalnum(input[i])) {
            good = true;
            end = i;
            break;
        }
    }

    if (not good) {
        input.clear();
        return false;
    }

    input.erase(input.begin(), input.begin() + first);
    end -= first;
    input.erase(input.begin() + end + 1, input.begin() + input.size());

    return true;

}

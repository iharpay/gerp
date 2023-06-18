/* main.cpp
*
* Ayah and Josh
* 4/20/2023
* Purpose: main file for GERP program. checks command line arguments, 
builds a file tree, runs gerp program.
*
*/

#include <string>
#include <iostream>
#include <fstream>

#include "Gerp.h"

using namespace std;

/* main
* purpose: This function checks if 
the user provided the correct number of arguments.
It then Builds a file tree from the directory which 
the user provides. Then main creates a Gerp objejct 
and calls the run command.
arguments: The number of arguments the user inputs
on the command line along with each argument
that is passed on the command line. (IE: argv[0] 
must always be ./gerp in this case)
returns: An int 0 if the program works, or 
exit(EXIT_FAILURE) if the program fails.
effects:
*/
int main(int argc, char *argv[]) {

    // DID THE USER PROVIDE THE CORRECT # OF ARGUMENTS?
    if (argc != 3) {
        cerr << "Usage: ./gerp inputDirectory outputFile";
        exit(EXIT_FAILURE);
    }

    // ATTEMPT TO OPEN THE INPUT DIRECTORY
    ifstream infile;
    infile.open(argv[1]);

    if (not infile.is_open()) {
        cerr << "Error: Unable to open file " << argv[1] << endl;
        exit(EXIT_FAILURE);
    }

    // ASSUMING WE HAVE A WORKING DIRECTORY:

    // BUILD A FILE TREE FROM THE INPUT DIRECTORY
    FSTree file_tree(argv[1]);

    // CREATE A GERP OBJECT AND PASS THE FILE TREE AND 
    // PROVIDED OUTPUT FILE TO ITS "RUN" FUNCTION
    string output = argv[2];
    Gerp my_gerp;
    my_gerp.run(file_tree.getRoot(), output);
    return 0;

}

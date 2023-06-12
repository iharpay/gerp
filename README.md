Ayah Harper and Josh Bernstein | Project 4: GERP | 4/30/2023

Program Purpose:
    
    The purpose of this program is to implement a version of the unix
    grep program, which indexes a directory and allows the user to 
    search for sequences of characters within that directory.

Acknowledgement:
    
    Timely Piazza responses!

Files:

    unit_tests.h: unit testing for stringProcessing.h

    main.cpp: Main file for the GERP program 

    stringProcessing.h:This is the decleration 
    of stripNonAlphaNum, which plays a huge
    role in our program because 
    it allows us to properly hash in
    words.

    stringProcessing.cpp:The purpose of 
    this file is to host a function which 
    strips non alphanumeric characters
    from a given word.


    HashTable.cpp:
    The purpose of this file
    is to create and implement a hash table
    in order to reach O(1) time complexity
    in retrieving stored data from files
    we got in gerp.cpp. This file plays a bigger
    role in our program by creating a hashtable which
    allows our program to run in specific time constraints
    given hash table's O(1) time complexity!

    HashTable.h:The purpose of this file
    is to initialize our hashTable methods. 
    under the hood, the hash table is implemented
    as a vector. This file again serves a greater
    purpose in our program by allowing us to store
    data and retrieve it in O(1) time. 

    Gerp.cpp: This is the implementation of our 
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

    Gerp.h:This is where we initialize
    the methods of my Gerp class. Our Gerp class
    and it's purpose/function purposes are explained
    in greater detail in my gerp.cpp purpose
    in gerp.cpp and overall in the README. But, this file
    plays a greater role in my overall program because it
    sets up my ability to create an instance of Gerp,
    run queries, and index throuhg the hashtabe that we 
    created.

    Word.h:This file holds
    our word struct. This holds 
    a file id to represent each file,
    the word that the struct is assigned to,
    the line number the word comes from
    along with the contents of the line.
    This is assigned to each line we put into
    our hash table.
    
    tiny_test.in: testing file for tinyData directory

    small_test.in: testing file for smallGutenberg

    medium_test.in: testing file for mediumGutenberg

    random_error.txt: Tests a bunch of junk input
    to ensure that nothing wrong is outputted. No 
    rhyme or reason as to what contents are.

    change_output.txt: Testing changing output files.

    no_quit_command: Tests that we reach the goodbye 
    message at the EOF without a @q command.

    single_character: Testing that single alphanumeric
    and nonalphanumeric characters have correct output.
    
    i_testing: Testing that i, I, and @i i all work 
    Srespectively

    vpasm10_test.txt: This is a copied version of vpasm from 
    smallGutenberg!

    large_test.in: Tests words from largeGutenberg 

Compile/run:

    Compile using "make gerp" command
    Run using "./gerp inputDirectory outputFile"

Architectural Overview:

    In main.cpp, we pass the name of the user-provided input
    directory to an FSTree constructor to build a file tree.
    We then construct a Gerp object and call its "run"
    function, which accepts the root of the file tree (in the
    form of a DirNode pointer) and the name of the 
    output file to send to output data to. From here, the
    main function has done its job and Gerp's run function 
    takes over, using its helper functions: it starts by 
    using the file tree to populate a vector of file paths 
    that will later allow the program to access each file. 
    Then, it opens up each file in the directory and parses
    through each word in the file (avoiding duplicate words
    from the same line) and builds a Word struct for each 
    word. Immediately after a Word struct is created in 
    Gerp.cpp, it is passed to the hashTable's hashIn
    function which deals with computing the hash index 
    and inserting the word (its key) and its associated 
    struct of information (its value) into the hash table. 
    After hashing the word into the hash table, the 
    program returns to Gerp.cpp, deletes the instance of 
    the word struct created there, and continues parsing
    words until every word from every file has been read in
    and hashed into the table-- at which point the index
    has been completely built. Then, the query function
    within Gerp.cpp starts accepting queries from the user.
    After taking in each query, within Gerp.cpp starts accepting queries from
    the user and passing these queries to the HashTable's
    hashOut function, which computes the index of the 
    string queried and writes data directly to the output file
    based on its findings. Additionally, the stripNonAlphaNum
    function is used in HashTable.cpp before entering each
    word into the hash table, as well as in Gerp.cpp before 
    searching for the string provided by the user.

Data Structures/Algorithms:

    Struct: We used a struct to represent each word in the file. 
    This way, when entering words into our hash table, we could
    use the word itself as the key and the struct that 
    packaged all of its associated information (i.e. line number,
    file number, line content, etc) as the value. Also, 
    since we decided to use chaining for our hash table, this 
    was a good choice that allowed us to store keys and values 
    together, which made for more efficient
    retrieval. The struct was also convenient for storing multiple
    copies of the same word, specifically its lowercase form
    (the copy that is actually used to compute its hash index)
    and its raw form (the copy of the word exactly as it appears
    in the file).

    List: We used a list of word structs to represent each "slot" in the 
    hashTable, because we decided to handle our collisions 
    using chaining. This was convenient for hashing elements
    in, because we could easily append each word struct onto
    the existing list at its corresponding index (list push_back
    operation occurs in O(1) time). This was also convenient
    for retrieving elements, since we could simply compute the
    index of the word to find, then iterate through the list
    (O(n), where n is number of elements) at that index to 
    search for its match. Since we dynamically resized the 
    hashTable to monitor the load factor, the number of elements
    at each table index was always pretty evenly balanced.
    The biggest disadvantage for linked lists is
    that it has slower access time and extra memory usage. 
    These flaws weren't too applicable for us, though,
    because our linked lists were never very long, meaning
    our O(n) time complexity to traverse the list
    was fairly short. 

    Vector: We used a vector of lists of word structs for the
    under the hood implementation of the hash table. Vectors 
    are perfect for hash tables because of their ability to 
    change in size, which was crucial for monitoring the
    load factor of the table and dynamically resizing as the
    number of elements increased. The vector was also perfect
    for inserting into the hash table, since we could 
    compute the hash index and insert the associated value 
    into the vector at that index in O(1) time. Retrieval
    from the vector could also happen in O(1) time, since 
    we again could use the hash function to compute the 
    index of the word to find, then access the list at
    that index # in O(1) time. A disadvtange
    for vectors are that it uses excessive memory
    and can sometimes be greedy. This is an issue, which
    is why we avoided using a vector for our main data 
    strucuture. Rather, we threw it in there as a way
    of holding "a list of word structs". This used
    up less memory than say using a vector instead of  a hash table to hold each word from each file
    in a given directory.

    HashTable: The main data structure for this program was a
    hashtable. We build the hashtable because it is a way 
    of storing data with a key-value pair along with 
    accessing the data with an O(1) time complexity.
    This allows for efficient data storage/retrieval. 
    We built our table with a vector so that it can be 
    dynamically allocated, and have a resize() method
    to stay at a stable load factor of .75.
    We also added some other methods that are basic
    to a hashtable, such as add or search. Some pros
    of using a hashtable for our program specifically include
    having efficient and fast data storage/retrieval, as 
    discussed. We are able to handle different sized input files.
    This means directories like tinyData which are small can easily
    use a hashtable, and largeGutenberg, a much much larger 
    directory can ALSO use a hash table. It is also important to 
    note that both directories use a hashtable which maintains a .75
    load factor too! Some cons include collissions, which we dealt 
    with through chaining. Hashtables can also use a lot of memory, which
    is mostly why we used linked lists to deal with 
    chaining (memory efficient). Another con includes the inability 
    to order our table, which is less important for our program
    since we really have no benefit of ordering each word (our data)
    in the hash table. 

    Set: We used a set to get rid of duplicates
    for each line. Basically, we infiled each word from each line
    into a set, that way each line was a unique 
    collection of words in that
    line without duplicates. THis was good since we were not supposed
    to cout the same words from the same lines. The pros of a set 
    are that it is unordered and duplicate free, which is great for us.
    We do NOT care about the order of our words, which is also why
    we used a hashtale. We obviously also wanted 
    a duplicate free data structure, thus sets came in! 
    Some cons of sets are that they are kind of slow,
    taking O(log n) for operations like insertion.
    They also use morememory than other data structures like
    a simple array or list. This is because each element is
    stored in a seperate location. This being said, sets played a
    crutial role in our program, by allowing us to get duplicate free
    lines while still having efficient run time / memore usage.

Testing:

    - In phase one, we tested stripNonAlphaNum using unit tests, which 
    tested stripping nonalphanumeric characters from just the front,
    just the end, then both the front and end of a word. The unit tests 
    also tested for edge cases, such as strings with a lot of nonalphanumeric
    characters sandwiched around them, strings with only nonalphanumeric
    characters and strings with no alphanumeric characters.
    - Also in phase one, we tested the FSTreeTraversal function using
    a separate main function where we gave it an input directory and 
    had it output the the path of each file it found. We tested this 
    on tinyData, where we knew the exact layout of the directory and 
    could check if the file paths were accurate.
    - Once we started working on a system to build the index, we tested each 
    function linearly as we wrote it:
        - populate_FilePaths: This was essentially the same as the 
        treeTraversal function. After populating the file_paths
        vector using this function, we tested to ensure that all 
        files were there by iterating over the vector and coutting 
        the string at each index. It was only efficient to cout for
        tinyData; for small, medium, and large Gutenberg, we just
        coutted the size of the vector and ensured it was equal to 
        the number of files in the directory (provided by dataSetInfo.txt).
        - buildIndex: Within build index, we iterated through each 
        file and parsed through each line, pushing all of the words in 
        each line into a set so as to prevent duplicate words from 
        the same line. When working with tinyData, we were able to 
        cout each line as it was read in (to ensure we were gettting
        all words from all lines), as well as each word in the set of 
        words in that line (to ensure that it was duplicate-free).
        - hashIn: When working with tinyData, we coutted the index 
        of each word alongside the word being hashed to ensure that
        words that were the same in their lowercase form were being
        sent to the same table index. We had the program cout a 
        message each time the load factor was increased and it had
        to call upon the re-up function.
        - re_up: When working with tinyData, we would cout the
        new index of each word being hashed alongside the word itself
        to ensure that words identical in their lowercase
        forms were still being sent to the same index in the 
        new hash table. At a few points in the small/medium Data
        sets, the program was reporting that it was not finding
        words that the reference was finding-- this meant that 
        we had to put flagging cerr statements in this function as 
        well as hashIn to ensure that the word was being hashed 
        into the table, and that its variations were not separated
        during the rehashing process.
        - hashOut: cerr statements to show the "hash out" index, 
        which we cross checked with that same word's "hash in" 
        index. cerr statements to print out the entire list at 
        the index. cerr statements that indicated when we arrived
        at a "raw" match as well as a case-insensitive match, 
        which helped for testing the @i query.

    We tested the overall program by creating input files with 
    various queries that asked GERP to search for strings that 
    both were and were not in the file. We ensured that our output
    was correct by diffing our sorted output files with the reference,
    and debugged the problems we saw.

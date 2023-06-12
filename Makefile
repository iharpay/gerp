CXX      = clang++
CXXFLAGS = -g -Wall -Wextra
LDFLAGS  = -g


unit_test: unit_test_driver.o stringProcessing.o
	$(CXX) $(CXXFLAGS) $^

stringProcessing.o: stringProcessing.cpp stringProcessing.h
	$(CXX) $(CXXFLAGS) -c stringProcessing.cpp

FSTreeTraversal.o: FSTreeTraversal.cpp DirNode.h FSTree.h
	$(CXX) $(CXXFLAGS) -c FSTreeTraversal.cpp

Gerp.o: Gerp.cpp Gerp.h stringProcessing.h HashTable.h DirNode.h FSTree.h
	$(CXX) $(CXXFLAGS) -c Gerp.cpp

HashTable.o: HashTable.cpp HashTable.h DirNode.h FSTree.h Word.h stringProcessing.h
	$(CXX) $(CXXFLAGS) -c HashTable.cpp

main.o: main.cpp Gerp.h FSTree.h HashTable.h DirNode.h Word.h
	$(CXX) $(CXXFLAGS) -c main.cpp

gerp: main.o Gerp.o HashTable.o stringProcessing.o DirNode.o FSTree.o
	$(CXX) $(LDFLAGS) -o gerp main.o Gerp.o HashTable.o stringProcessing.o DirNode.o FSTree.o

provide: 
	provide comp15 proj4_gerp README Makefile Gerp.cpp Gerp.h \
	stringProcessing.h HashTable.h DirNode.h FSTree.h HashTable.cpp \
	Word.h main.cpp stringProcessing.cpp tiny_test.in small_test.in \
	medium_test.in random_error.txt no_quit_command.txt \
	i_testing.txt change_output.txt 

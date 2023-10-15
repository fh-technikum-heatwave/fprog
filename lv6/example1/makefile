CXX       = clang++
CXXFLAGS  = -g -std=c++17 -Wall

$(PROGRAM): readFile.cpp
	$(CXX) $(CXXFLAGS) readFile.cpp -o $(PROGRAM)

.PHONY: clean 

all: readFile readFile2

readFile: readFile.cpp
	$(CXX) $(CXXFLAGS) readFile.cpp -o readFile

readFile2: readFile2.cpp
	$(CXX) $(CXXFLAGS) readFile2.cpp -o readFile2


clean:
	-rm -f *.o $(PROGRAM) 

dist: clean
	-tar -chvj -C .. -f ../$(PROGRAM).tar.bz2 $(PROGRAM)


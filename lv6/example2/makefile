CXX       = clang++
CXXFLAGS  = -g -std=c++17 -Wall

$(PROGRAM): invertMatrix.cpp
	$(CXX) $(CXXFLAGS) invertMatrix.cpp -o $(PROGRAM)

.PHONY: clean 

all: invertMatrix invertMatrix2

readMatrix: invertMatrix.cpp
	$(CXX) $(CXXFLAGS) invertMatrix.cpp -o invertMatrix

readMatrix2: invertMatrix2.cpp
	$(CXX) $(CXXFLAGS) invertMatrix2.cpp -o invertMatrix2	

clean:
	-rm -f *.o $(PROGRAM) 

dist: clean
	-tar -chvj -C .. -f ../$(PROGRAM).tar.bz2 $(PROGRAM)


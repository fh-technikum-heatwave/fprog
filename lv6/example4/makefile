PROGRAM   = division
CXX       = clang++
CXXFLAGS  = -g -std=c++17 -Wall

$(PROGRAM): division.cpp
	$(CXX) $(CXXFLAGS) division.cpp -o $(PROGRAM)

.PHONY: clean 

clean:
	-rm -f *.o $(PROGRAM) 

dist: clean
	-tar -chvj -C .. -f ../$(PROGRAM).tar.bz2 $(PROGRAM)


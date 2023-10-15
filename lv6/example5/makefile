PROGRAM   = ascii
CXX       = clang++
CXXFLAGS  = -g -std=c++17 -Wall

$(PROGRAM): ascii.cpp
	$(CXX) $(CXXFLAGS) ascii.cpp -o $(PROGRAM)

.PHONY: clean 

clean:
	-rm -f *.o $(PROGRAM) 

dist: clean
	-tar -chvj -C .. -f ../$(PROGRAM).tar.bz2 $(PROGRAM)


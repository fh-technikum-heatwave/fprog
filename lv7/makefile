PROGRAM   = sorting
CXX       = g++
CXXFLAGS  = -g -std=c++20 -Wall

$(PROGRAM): sorting.cpp
	$(CXX) $(CXXFLAGS)  sorting.cpp -o $(PROGRAM)

.PHONY: clean 

clean:
	-rm -f *.o $(PROGRAM) 

dist: clean
	-tar -chvj -C .. -f ../$(PROGRAM).tar.bz2 $(PROGRAM)


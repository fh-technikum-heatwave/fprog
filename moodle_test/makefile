PROGRAM   = b1
CXX       = clang++
CXXFLAGS  = -g -std=c++17 -Wall

$(PROGRAM): b1.cpp
	$(CXX) b1.cpp -o $(PROGRAM)

.PHONY: clean 

clean:
	-rm -f *.o $(PROGRAM) 

dist: clean
	-tar -chvj -C .. -f ../$(PROGRAM).tar.bz2 $(PROGRAM)


CXX = g++

CXXFLAGS = -c -g -Wall -std=c++17

PROGRAM = CodingOneAssignment.exe

CPPFILES = main.cpp randomNumGen.cpp unionFind.cpp


run:
	$(CXX) $(CXXFLAGS) $(CPPFILES)
	$(CXX) -o $(PROGRAM) *.o
	./$(PROGRAM)

clean:
	rm -f $(PROGRAM) *.o


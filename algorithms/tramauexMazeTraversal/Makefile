CXX = g++

CXXFLAGS = -c -g -Wall -std=c++17

PROGRAM = CodingTwoAssignment.exe

CPPFILES = main.cpp maze.cpp


run:
	$(CXX) $(CXXFLAGS) $(CPPFILES)
	$(CXX) -o $(PROGRAM) *.o
	./$(PROGRAM)

clean:
	rm -f $(PROGRAM) *.o
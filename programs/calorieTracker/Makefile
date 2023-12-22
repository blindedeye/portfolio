CXX = g++

CXXFLAGS = -c -g -Wall -std=c++17

PROGRAM = calorieProgram.exe

CPPFILES = main.cpp userCheck.cpp home.cpp utility.cpp


run:
	$(CXX) $(CXXFLAGS) $(CPPFILES)
	$(CXX) -o $(PROGRAM) *.o
	./$(PROGRAM)

runtest:
	$(CXX) $(CXXFLAGS) $(CPPFILES)
	$(CXX) -o $(PROGRAM) *.o
	./$(PROGRAM) < input.txt

clean:
	rm -f $(PROGRAM) *.o


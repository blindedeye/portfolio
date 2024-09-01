CXX = g++

CXXFLAGS = -c -g -Wall -std=c++17

PROGRAM = hangman.exe

CPPFILES = main.cpp mainmenu.cpp stages.cpp utility.cpp words.cpp game.cpp


build:
	$(CXX) $(CXXFLAGS) $(CPPFILES)
	$(CXX) -o $(PROGRAM) *.o


clean:
	rm -f $(PROGRAM) *.o


run:
	./$(PROGRAM)

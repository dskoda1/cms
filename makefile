CXX= clang++
CXXFLAGS= -Wfatal-errors -std=c++1z -Wall -Wextra -pedantic -g 


all: Main

Main: Main.o
		$(CXX) $(CXXFLAGS) -o cms Main.o

Main.o: Main.cpp 
		$(CXX) $(CXXFLAGS) -c Main.cpp
		  
clean: 
		rm -rf *.o *.gch cms

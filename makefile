CXX= g++
CXXFLAGS= -g -Wfatal-errors -std=c++1z -Wall -Wextra -pedantic


all: Main

Main: Main.o
		$(CXX) $(CXXFLAGS) -o cms Main.o

Main.o: Main.cpp ${HEADERS}
		$(CXX) $(CXXFLAGS) -c Main.cpp
		  
HEADERS: commands/*.hpp io/*.hpp market/*.hpp util/*.hpp

clean: 
		rm -rf *.o *.gch cms

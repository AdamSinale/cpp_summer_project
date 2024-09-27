# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -std=c++17

# Include directories (SFML system-wide)
INCLUDES = -I/usr/include

# Linker flags for SFML
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

# Object files
OBJ = main.o board.o game.o property.o

# Executable name
EXEC = monopoly

# Rule to compile the project
all: $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(EXEC) $(LDFLAGS)

# Rules to compile individual files
main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp $(INCLUDES)

board.o: board.cpp board.hpp
	$(CXX) $(CXXFLAGS) -c board.cpp $(INCLUDES)

game.o: game.cpp game.hpp
	$(CXX) $(CXXFLAGS) -c game.cpp $(INCLUDES)

property.o: property.cpp property.hpp
	$(CXX) $(CXXFLAGS) -c property.cpp $(INCLUDES)

clean:
	rm -f *.o $(EXEC)

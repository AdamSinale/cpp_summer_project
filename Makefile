# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++17 -Wall -Wextra -g

# Sources
SOURCES = main.cpp player.hpp property.cpp board.cpp game.cpp

# Objects (same as source files but with .o extension)
OBJECTS = $(SOURCES:.cpp=.o)

# Executable target name
TARGET = monopoly

# Default target (the first target is the one that runs when you just type `make`)
all: $(TARGET)

# Rule for linking the object files to create the final executable
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

# Rule for compiling .cpp files into .o files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up object files and the executable
clean:
	rm -f *.o

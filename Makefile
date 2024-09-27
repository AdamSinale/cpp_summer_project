# Path to your SFML directory
SFML_DIR = ./SFML-2.5.1

# Compiler
CXX = g++
CXXFLAGS = -std=c++17 -Wall -I$(SFML_DIR)/include
LDFLAGS = -L$(SFML_DIR)/lib -lsfml-graphics -lsfml-window -lsfml-system -lGL -lGLU -Wl,-rpath=$(SFML_DIR)/lib

# Executable target
TARGET = monopoly

# Source files (no need to include player.hpp, it's included in cpp files)
SOURCES = main.cpp game.cpp board.cpp property.cpp

# Object files
OBJECTS = $(SOURCES:.cpp=.o)

# Build the project
all: $(TARGET)

# Link object files into the executable
$(TARGET): $(OBJECTS)
	$(CXX) -o $(TARGET) $(OBJECTS) $(LDFLAGS)

# Compile each source file into an object file
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

# Clean up build artifacts
clean:
	rm -f $(OBJECTS) $(TARGET)

.PHONY: all clean

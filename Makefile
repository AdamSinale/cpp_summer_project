# ID: 322453689
# MAIL: adam.sinale@gmail.com
CXX = g++
CXXFLAGS = -Wall -std=c++17

# Include directories (SFML system-wide)
INCLUDES = -I/usr/include
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

# Object files for the main game
OBJ = board.o game.o property.o main.o  # includes main.o for the game

# Object files for tests (exclude main.o)
TEST_OBJ = Test.o TestCounter.o board.o game.o property.o  # excludes main.o

EXEC = monopoly
TEST_EXEC = test

# Default target: builds the game
all: $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(EXEC) $(LDFLAGS)

# Compile the game executable
main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp $(INCLUDES)

board.o: board.cpp board.hpp
	$(CXX) $(CXXFLAGS) -c board.cpp $(INCLUDES)

game.o: game.cpp game.hpp
	$(CXX) $(CXXFLAGS) -c game.cpp $(INCLUDES)

property.o: property.cpp property.hpp
	$(CXX) $(CXXFLAGS) -c property.cpp $(INCLUDES)

# Compile and run tests (without main.cpp)
tests: $(TEST_OBJ)
	$(CXX) $(CXXFLAGS) $(TEST_OBJ) -o $(TEST_EXEC) $(LDFLAGS)
	./$(TEST_EXEC)

Test.o: Test.cpp
	$(CXX) $(CXXFLAGS) -c Test.cpp $(INCLUDES)

TestCounter.o: TestCounter.cpp
	$(CXX) $(CXXFLAGS) -c TestCounter.cpp $(INCLUDES)

# Clean up object files and executables
clean:
	rm -f *.o $(EXEC) $(TEST_EXEC)

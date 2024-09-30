# Monopoly Game Project - Adam Sin, 322453689

This project is a C++ implementation of a Monopoly-like game with a graphical interface using SFML (Simple and Fast Multimedia Library).

## Project Structure

- **main.cpp**: Entry point of the game, contains the main game loop and handles player turns.
- **game.cpp/game.hpp**: Contains the `Game` class, which handles game mechanics like moving players, handling dice rolls, and sending players to jail.
- **board.cpp/board.hpp**: Manages the game board, including properties and player positions, and draws the game board using SFML.
- **property.cpp/property.hpp**: Defines various types of properties (streets, utilities, railroads, etc.) and handles property-related mechanics such as rent collection.
- **player.hpp**: Defines the `Player` class, including player actions like moving, buying properties, and handling jail situations.
- **Makefile**: Build script for compiling the game, handling both system-wide SFML installations and local SFML directories.

## Prerequisites

The project depends on SFML for rendering the graphical interface. You can either use the system-wide installation of SFML or the provided `SFML-2.5.1` folder included with the project.

### System Requirements:
- **C++17** or higher
- **SFML** (system-wide or local)

### Installing SFML

#### Option 1: Using System-wide SFML

- **Linux (Debian/Ubuntu)**:
  ```bash
  sudo apt-get install libsfml-dev

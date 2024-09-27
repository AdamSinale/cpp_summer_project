# Monopoly Game Project

This project is a C++ implementation of the basic Monopoly game with a graphical interface using SFML.


## Description
  - The game is fit to 2-8 players.
  - The board is dynamic! Meaning you can construct your own board.
  - The last to have cash or the first to reach 4000 wins.
  - step on someone's property / tax space / jail without enough money and you're out.
    (in the case of someone's property, your property goes to him)
     
## Project Structure

- **main.cpp**: Entry point of the game, contains the main game loop and handles player turns and GUI display.
- **game.cpp/game.hpp**: Contains the `Game` class, which handles game mechanics like moving players, handling dice rolls, and sending players to jail.
- **board.cpp/board.hpp**: Manages the game board, includes properties list, and draws the game board using SFML.
- **property.cpp/property.hpp**: Defines various types of properties (streets, utilities, railroads, etc.) and handles property-related mechanics such as rent collection. 
- **player.hpp**: Defines the `Player` class, including player actions like moving, buying properties, and handling jail situations.
- **Makefile**: Build script for compiling the game, handling both system-wide SFML installations and local SFML directories.
* When a player gets to position i, game will call boards i-th property, which will handle the action  by its derived class from Property
  
## Prerequisites

The project depends on SFML for rendering the graphical interface. You can either use the system-wide installation of SFML or the provided `SFML-2.5.1` folder included with the project.

### System Requirements:
- **C++17** or higher
- **SFML** (system-wide or local)

### Installing SFML

- **Linux (Debian/Ubuntu)**:
  ```bash
  sudo apt-get install libsfml-dev


#ifndef BOARD_HPP
#define BOARD_HPP

#include <SFML/Graphics.hpp>
#include "player.hpp"

class Board {
    vector<shared_ptr<Property>> spaces;
public:
    Board();
    void addSpace(shared_ptr<Property> p);
    void displayBoard(sf::RenderWindow& window, const vector<shared_ptr<Player>>& players);
    int jailPosition();
    int boardSize(){ return spaces.size(); }
    shared_ptr<Property>& getProperty(int i){ return spaces[i]; }
};

#endif

#ifndef BOARD_HPP
#define BOARD_HPP

#include "player.hpp"

class Board {
    vector<shared_ptr<Property>> spaces;
public:
    Board();
    void addProperty(shared_ptr<Property> property);
    void printBoard();
    int boardSize(){ return spaces.size(); }
    shared_ptr<Property>& getProperty(int i){ return spaces[i]; }
};

#endif

#ifndef BOARD_HPP
#define BOARD_HPP

#include "player.hpp"

class Board {
    vector<shared_ptr<Property>> spaces;
public:
    Board();
    void addSpace(shared_ptr<Property> p){ spaces.push_back(p); }
    void printBoard();
    int jailPosition();
    int boardSize(){ return spaces.size(); }
    shared_ptr<Property>& getProperty(int i){ return spaces[i]; }
};

#endif
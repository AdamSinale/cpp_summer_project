#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "property.hpp"

class Player {
    string name;
    int balance = 1500;
    int position = 0;
    vector<shared_ptr<Property>> ownedProperties;
    bool inJail = false;
    int jailTurns = 0;;
public:
    Player(const string& n) : name(n){}
    string getName(){ return name; }
    int getBalance(){ return balance; }
    void move(int steps, int boardSize){ position = (position+steps)%boardSize; };
    int getPosition(){ return position;}
    void changeBalance(int amount){ balance += amount; };
    void buyProperty(std::shared_ptr<Property> property);
    void goToJail();
    void releaseFromJail();
    bool isBankrupt() const;

};

#endif

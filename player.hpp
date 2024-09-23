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
    int getPosition(){ return position;}
    vector<shared_ptr<Property>> getProperties(){ return ownedProperties; }

    void move(int steps, int boardSize){ position = (position+steps)%boardSize; };
    void changeBalance(int amount){ balance += amount; };
    void addProperty(shared_ptr<Property> p){ ownedProperties.push_back(p); };
    void goToJail();
    void releaseFromJail();
    bool isBankrupt() const;

};

#endif

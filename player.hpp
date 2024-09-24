#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "property.hpp"

class Player {
    string name;
    int balance = 1500;
    int position = 0;
    int rolled = 0;
    vector<shared_ptr<Property>> ownedProperties;
    int jailTurns = 0;
    int outOfJailCards = 0;
public:
    Player(const string& n) : name(n){}
    string getName(){ return name; }
    int getBalance(){ return balance; }
    int getPosition(){ return position; }
    int getRolled(){ return rolled; }
    int getOutOfJailCards(){ return outOfJailCards; }
    void setRolled(int r){ rolled = r; }
    vector<shared_ptr<Property>> getProperties(){ return ownedProperties; }

    void goToJail(){ jailTurns=3; }
    void outOfJail(){ jailTurns=0; }
    bool isInJail(){ return jailTurns>0; }
    void jailTurn(){ jailTurns--; }
    void useOutOfJailCard(){ outOfJailCards--; }

    void transferAll(shared_ptr<Player> o){
        if(o != nullptr){ o->changeBalance(getBalance()); }
        for(auto& p : getProperties()){
            if(o != nullptr){ o->addProperty(p); }
            p->setOwner(o);
        }
    }
    void move(int steps, int boardSize){ position = (position+steps)%boardSize; }
    void changeBalance(int amount){ balance += amount; };
    void addProperty(shared_ptr<Property> p){ ownedProperties.push_back(p); }
    bool isBankrupt() const{ return balance <= 0; };

    friend ostream& operator<<(ostream& os, Player& p){ os<<p.getName(); return os; }
};

#endif

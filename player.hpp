// ID: 322453689
// MAIL: adam.sinale@gmail.com
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
    void setPosition(int n){ if(n>0){position=n;} else{position=0;} }
    vector<shared_ptr<Property>>& getProperties(){ return ownedProperties; }

    void addOutOfJailCard(){ outOfJailCards++; }
    void goToJail(){ jailTurns=3; }
    void outOfJail(){ jailTurns=0; }
    bool isInJail(){ return jailTurns>0; }
    void jailTurn(){ jailTurns--; }
    void useOutOfJailCard(){ outOfJailCards--; outOfJail(); }

    bool sameColorLevel(Street s){
        for(auto& p : s.getGroup()){
            if(p->getColor()!=""){                // is a street
                if(s.getColor()==p->getColor()){  // are same color
                    if(p->getNumHouses()<s.getNumHouses()){ // not on the same level
                        cout << "Upgrade " << p->getName() << "first" << endl;
                        return false;
                    } if(p->getOwner() != s.getOwner()){ // under else's ownership
                        cout << "You dont have the full color" << endl;
                        return false;
                    }
                }
            }
        } 
        return true;
    }
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

    friend ostream& operator<<(ostream& os, Player& p){ os<<"\033[31m"<<p.getName()<<"\033[0m"; return os; }
};

#endif

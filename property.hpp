
#ifndef PROPERTY_HPP
#define PROPERTY_HPP

#include <vector>
#include <tuple>
#include <iostream>
#include <memory> 
#include <climits> 
#include <queue>
#include <string>
#include <unordered_map> 
#include <random>
#include <chrono>
#include <algorithm>

using std::cout;
using std::endl;
using std::cin;
using std::weak_ptr;
using std::shared_ptr;
using std::make_shared;
using std::string;
using std::ostream;
using std::vector;

class Player;

class Property {
protected:
    string name;
    int price;
    weak_ptr<Player> owner;
public:
    Property(const string& n, int p) : name(n), price(p){}
    void setOwner(const shared_ptr<Player>& newOwner){ owner = newOwner; }
    
    shared_ptr<Player> getOwner() const{ return owner.lock(); }
    string getName() const{ return name; }
    int getPrice() const{ return price; }
    
    virtual void handleOwned(){ return; }
    virtual int calculateRent(int rolled=0) = 0;

    friend ostream& operator<<(ostream& os, Property& s);
};

class Railroad : public Property {
    int baseRent = 50;
public:
    Railroad(const string& n) : Property(n,200){};
    int calculateRent(int rolled);
};

class Street : public Property {
    int rent;
    int houseCost;
    int houseRent;
    int hotelRent;
    int numHouses = 0;
public:
    Street(const string& n,int p,int r,int h,int hr,int hotr) : Property(n,p),rent(r),houseCost(h),houseRent(hr),hotelRent(hotr){};
    void buildHouse();
    void buildHotel();
    int calculateRent(int rolled);
    void handleOwned() override;
};

class Utility : public Property {
public:
    Utility(const string& n) : Property(n,150){};
    int calculateRent(int rolled){ return rolled*10; };
};

class Surprise : public Property {
public:
    Surprise(const string& n) : Property(n,0){};
    int calculateRent(int rolled){ return rolled; };
};

#endif

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
    virtual bool whenLanded(shared_ptr<Player>& p) = 0;
    string getName() const{ return name; }
    int getPrice() const{ return price; }

    shared_ptr<Player> getOwner() const{ return owner.lock(); }
    void setOwner(const shared_ptr<Player>& newOwner){ owner = newOwner; }
    friend ostream& operator<<(ostream& os, Property& s);
};

class Railroad : public Property {
    int baseRent = 50;
public:
    Railroad(const string& n) : Property(n,200){};
    bool whenLanded(shared_ptr<Player>& p) override;
    int calculateRent();
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
    bool whenLanded(shared_ptr<Player>& p) override;
    int calculateRent();
};
class Utility : public Property {
public:
    Utility(const string& n) : Property(n,150){};
    bool whenLanded(shared_ptr<Player>& p) override;
    int calculateRent(int rolled){ return rolled*10; };
};

class Surprise : public Property {
public:
    Surprise(const string& n) : Property(n,0){};
    bool whenLanded(shared_ptr<Player>& p) override{ return false; }
};
class Start : public Property {
public:
    Start(const string& n) : Property(n,0){};
    bool whenLanded(shared_ptr<Player>& p) override;
};
class Parking : public Property {
public:
    Parking(const string& n) : Property(n,0){};
    bool whenLanded(shared_ptr<Player>& p) override;
};
class Tax : public Property {
public:
    Tax(const string& n) : Property(n,0){};
    bool whenLanded(shared_ptr<Player>& p) override;
};
class GoToJail : public Property {
public:
    GoToJail(const string& n) : Property(n,0){};
    bool whenLanded(shared_ptr<Player>& p) override;
};
class Jail : public Property {
public:
    Jail(const string& n) : Property(n,0){};
    bool whenLanded(shared_ptr<Player>& p) override;
};

#endif
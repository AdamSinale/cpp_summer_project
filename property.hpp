
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
using std::unique_ptr;
using std::make_shared;
using std::make_unique;
using std::string;
using std::ostream;
using std::vector;

class Player;

class Property {
protected:
    string name;
    weak_ptr<Player> owner;
public:
    Property(){ cout << "enter name"<< endl; cin >> name;}
    Property(const string& n) : name(n){}
    ~Property(){}
    virtual bool whenLanded(shared_ptr<Player>& p) = 0;
    string getName() const{ return name; }
    friend ostream& operator<<(ostream& os, Property& s);
    int getPrice() const{ return 0; }
    int getNumHouses(){ return 0; }
    void setOwner(const shared_ptr<Player>& newOwner){ owner = newOwner; }
};

class Railroad : public Property {
    int price = 200;
    int baseRent = 50;
public:
    Railroad() : Property(){}
    Railroad(const string& n) : Property(n){};
    ~Railroad(){}
    bool whenLanded(shared_ptr<Player>& p) override;
    int calculateRent();
    int getPrice() const{ return price; }
    shared_ptr<Player> getOwner() const{ return owner.lock(); }
};
class Street : public Property {
    int price;
    int rent;
    int houseCost;
    int houseRent;
    int hotelRent;
    int numHouses = 0;
public:
    Street() : Property(){
        cout << "price, rent, house cost, house rent, hotel rent" << endl;
        cin >> price >> rent >> houseCost >> houseRent >> hotelRent;
    }
    Street(const string& n,int p,int r,int h,int hr,int hotr) : Property(n),price(p),rent(r),houseCost(h),houseRent(hr),hotelRent(hotr){};
    ~Street(){}
    void buildHouse();
    void buildHotel();
    bool whenLanded(shared_ptr<Player>& p) override;
    int calculateRent();
    int getNumHouses(){ return numHouses; }
    int getPrice() const{ return price; }
    shared_ptr<Player> getOwner() const{ return owner.lock(); }
};
class Utility : public Property {
    int price = 150;
public:
    Utility() : Property(){}
    Utility(const string& n) : Property(n){};
    ~Utility(){}
    bool whenLanded(shared_ptr<Player>& p) override;
    int calculateRent(int rolled){ return rolled*10; };
    int getPrice() const{ return price; }
    shared_ptr<Player> getOwner() const{ return owner.lock(); }
};

class Chest : public Property {
public:
    Chest() : Property(){}
    Chest(const string& n) : Property(n){};
    ~Chest(){}
    bool whenLanded(shared_ptr<Player>& p) override;
};
class Start : public Property {
public:
    Start() : Property(){}
    Start(const string& n) : Property(n){};
    ~Start(){}
    bool whenLanded(shared_ptr<Player>& p) override;
};
class Parking : public Property {
public:
    Parking() : Property(){}
    Parking(const string& n) : Property(n){};
    ~Parking(){}
    bool whenLanded(shared_ptr<Player>& p) override;
};
class Tax : public Property {
public:
    Tax() : Property(){}
    Tax(const string& n) : Property(n){};
    ~Tax(){}
    bool whenLanded(shared_ptr<Player>& p) override;
};
class GoToJail : public Property {
public:
    GoToJail() : Property(){}
    GoToJail(const string& n) : Property(n){};
    ~GoToJail(){}
    bool whenLanded(shared_ptr<Player>& p) override;
};
class Jail : public Property {
public:
    Jail() : Property(){}
    Jail(const string& n) : Property(n){};
    ~Jail(){}
    bool whenLanded(shared_ptr<Player>& p) override;
};

class Surprise : public Property {
public:
    Surprise() : Property(){}
    Surprise(const string& n) : Property(n){};
    ~Surprise(){}
    bool whenLanded(shared_ptr<Player>& p) override;
};
class Get50 : public Surprise {
public:
    Get50(string n) : Surprise(n){}
    ~Get50(){}
    bool whenLanded(shared_ptr<Player>& p) override;
};
class Back3Steps : public Surprise {
public:
    Back3Steps(string n) : Surprise(n){}
    ~Back3Steps(){}
    bool whenLanded(shared_ptr<Player>& p) override;
};
class Repair : public Surprise {
public:
    Repair(string n) : Surprise(n){}
    ~Repair(){}
    bool whenLanded(shared_ptr<Player>& p) override;
};
class OutOfJail : public Surprise {
public:
    OutOfJail(string n) : Surprise(n){};
    ~OutOfJail(){}
    bool whenLanded(shared_ptr<Player>& p) override;
};

#endif
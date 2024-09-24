#include "property.hpp"
#include "player.hpp"

ostream& operator<<(ostream& os, Property& s){
    os << s.getName() << " "<< s.getPrice() <<"M";
    return os;
}

bool Railroad::whenLanded(shared_ptr<Player>& p){
    if(getOwner() == p){ return false; }
    else if(getOwner() == nullptr){
        if(p->getBalance() < getPrice()){ cout<<"Can't buy"<<endl; return false;}
        char ans;
        cout << "Wanna buy? (y/n)" << endl;
        cin >> ans;
        if(ans=='y' || ans=='Y'){ 
            setOwner(p); 
            p->changeBalance(-getPrice()); 
            return true;
        }
    }
    else{
        cout << "You have to pay rent to " << *getOwner() << endl;
        int rent = calculateRent();
        p->changeBalance(-rent);
        getOwner()->changeBalance(rent);
        if(p->getBalance() < 0){ p->transferAll(getOwner()); }
    }
    return false;
}
int Railroad::calculateRent(){
    int rails = 0;
    for (const auto& property : getOwner()->getProperties()) {
        if (dynamic_cast<Railroad*>(property.get())) {
            rails++;
        }
    }
    return rails*50;
}

bool Street::whenLanded(shared_ptr<Player>& p){
    if(getOwner() == p){
        if(numHouses==5){ cout<<"Got to your hotel"<<endl; return false; }
        else{
            if((numHouses<4 && p->getBalance()<houseCost) || p->getBalance()<houseCost*4+100){ 
                cout<<"Can't buy"<<endl; return false;
            }
            char ans;
            cout << "Wanna upgrade? (y/n)" << endl;
            cin >> ans;
            if(ans=='y' || ans=='Y'){ 
                numHouses++; p->changeBalance(-price);
                return true;
            }
        } 
    }
    else if(getOwner() == nullptr){
        if(p->getBalance() < getPrice()){ cout<<"Can't buy"<<endl; return false;}
        char ans;
        cout << "Wanna buy? (y/n)" << endl;
        cin >> ans;
        if(ans=='y' || ans=='Y'){ 
            setOwner(p); 
            p->changeBalance(-getPrice()); 
            return true;
        }
    }
    else{
        cout << "You have to pay rent to " << *getOwner() << endl;
        int rent = calculateRent();
        p->changeBalance(-rent);
        getOwner()->changeBalance(rent);
        if(p->getBalance() < 0){ p->transferAll(getOwner()); }
    }
    return false;
}
int Street::calculateRent(){
    if(numHouses==0){ return rent; }
    else if(numHouses==5){ return hotelRent; }
    int price = houseRent;
    for(int i=1; i<numHouses; i++){ price *= 2; }
    return price;
}

bool Utility::whenLanded(shared_ptr<Player>& p){
    if(getOwner() == p){ return false; }
    else if(getOwner() == nullptr){
        if(p->getBalance() < getPrice()){ cout<<"Can't buy"<<endl; return false;}
        char ans;
        cout << "Wanna buy? (y/n)" << endl;
        cin >> ans;
        if(ans=='y' || ans=='Y'){ 
            setOwner(p); 
            p->changeBalance(-getPrice()); 
            return true;
        }
    }
    else{
        cout << "You have to pay rent to " << *getOwner() << endl;
        int rent = calculateRent(p->getRolled());
        p->changeBalance(-rent);
        getOwner()->changeBalance(rent);
        if(p->getBalance() < 0){ p->transferAll(getOwner()); }
    }
    return false;
}

bool Start::whenLanded(shared_ptr<Player>& p){
    cout << "You landed on Tax! -100" << endl;
    p->changeBalance(200); 
    return false; 
}
bool Tax::whenLanded(shared_ptr<Player>& p){
    cout << "You landed on Tax! -100" << endl;
    p->changeBalance(-100); 
    return false; 
}
bool Parking::whenLanded(shared_ptr<Player>& p){
    cout << "You are parking! Turn ended" << endl;
    return false;
}
bool GoToJail::whenLanded(shared_ptr<Player>& p){
    cout << "Go to JAIL! for 3 turns" << endl;
    p->goToJail();
    return false;
}
bool Jail::whenLanded(shared_ptr<Player>& p){
    cout << "JAIL" << endl;
    return false;
}
#include "property.hpp"
#include "player.hpp"

ostream& operator<<(ostream& os, Property& s){
    os << s.getName() << " "<< s.getPrice() <<"M";
    return os;
}

string Railroad::getDisplay(){ 
    if(owner.lock()==nullptr){ return name+"\n"+std::to_string(price); }
    return name+"\n"+std::to_string(price) +"\n"+owner.lock()->getName()+"'s";
}
bool Railroad::whenLanded(shared_ptr<Player>& p){
    if(getOwner() == p){ return false; }
    else if(getOwner() == nullptr){
        if(p->getBalance() < getPrice()){ cout<<"Can't buy"<<endl; return false;}
        char ans;
        cout << "Wanna buy? You have " << p->getBalance() << " (y/n)" << endl;
        cin >> ans;
        if(ans=='y' || ans=='Y'){ 
            setOwner(p); 
            p->changeBalance(-getPrice()); 
            cout << "You now have " << p->getBalance() << endl;
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

string Street::getDisplay(){ 
    if(owner.lock()==nullptr){ return name+"\n"+std::to_string(price); }
    string built="";
    if(numHouses>0){ built="houses-"+std::to_string(numHouses); }
    if(numHouses==5){ built="hotel"; }
    return name+"\n"+std::to_string(price) +"\n"+owner.lock()->getName()+"'s. "+built;
}
bool Street::whenLanded(shared_ptr<Player>& p){
    if(getOwner() == p){
        if(numHouses==5){ cout<<"Got to your hotel"<<endl; return false; }
        else{
            if((numHouses<4 && p->getBalance()<houseCost) || p->getBalance()<houseCost*4+100){ 
                cout<<"Can't afford to upgrade"<<endl; return false;
            }
            if(!p->sameColorLevel(*this)){ return false; }
            char ans;
            cout << "Wanna upgrade? You have " << p->getBalance() << " (y/n)" << endl;
            cin >> ans;
            if(ans=='y' || ans=='Y'){ 
                numHouses++; p->changeBalance(-price);
                cout << "You now have " << p->getBalance() << endl;
                return true;
            }
        } 
    }
    else if(getOwner() == nullptr){
        if(p->getBalance() < getPrice()){ cout<<"Can't afford to buy"<<endl; return false;}
        char ans;
        cout << "Wanna buy? You have " << p->getBalance() << " (y/n)" << endl;
        cin >> ans;
        if(ans=='y' || ans=='Y'){ 
            setOwner(p); 
            p->changeBalance(-getPrice()); 
            cout << "You now have " << p->getBalance() << endl;
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

string Utility::getDisplay(){ 
    if(owner.lock()==nullptr){ return name+"\n"+std::to_string(price); }
    return name+"\n"+std::to_string(price) +"\n"+owner.lock()->getName()+"'s";
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
bool Chest::whenLanded(shared_ptr<Player>& p){
    cout << "You found a treasure! (random 100-400)" << endl;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(10,40);  // in jumps of 10
    int gift = dist(gen)*10;
    p->changeBalance(gift); 
    cout << "You got " << gift << "! You balance is " << p->getBalance() << endl;
    return false; 
}
bool Tax::whenLanded(shared_ptr<Player>& p){
    p->changeBalance(-100); 
    cout << "You landed on Tax! -100, You are left with " << p->getBalance() << endl;
    return false; 
}
bool Parking::whenLanded(shared_ptr<Player>& p){
    cout << *p << ", rest here. Turn ended" << endl;
    return false;
}
bool GoToJail::whenLanded(shared_ptr<Player>& p){
    cout << "Go to JAIL! for 3 turns" << endl;
    p->goToJail();
    return false;
}
bool Jail::whenLanded(shared_ptr<Player>& p){
    cout << *p << ", you're going to JAIL!" << endl;
    return false;
}

bool Surprise::whenLanded(shared_ptr<Player>& p){
    vector<unique_ptr<Property>> surprises;
    
    surprises.push_back(make_unique<Start>("surprise start"));
    surprises.push_back(make_unique<Get50>("50 dollars"));
    surprises.push_back(make_unique<Back3Steps>("3 steps back"));
    surprises.push_back(make_unique<Repair>("property repairs"));
    surprises.push_back(make_unique<Tax>("surprise tax"));
    surprises.push_back(make_unique<Jail>("surprise jail"));
    surprises.push_back(make_unique<OutOfJail>("out of jail"));
    
    int randomSurprise = rand() % surprises.size();
    surprises[randomSurprise]->whenLanded(p);
    return false;
}
bool Get50::whenLanded(shared_ptr<Player>& p){
    cout << "Bank pays you dividend of 50$. New balance - " << p->getBalance() << endl;
    p->changeBalance(50);
    return false;
}
bool Back3Steps::whenLanded(shared_ptr<Player>& p){
    cout << "Go back 3 steps" << endl;
    p->setPosition(p->getPosition()-3);
    return false;
}
bool Repair::whenLanded(shared_ptr<Player>& p){
    cout << "Make property repairs - 25$ per house, 100$ per hotel" << endl;
    for(auto& s : p->getProperties()){
        p->changeBalance(s->getNumHouses()*25);
        if(s->getNumHouses()==5){ p->changeBalance(100-25); }
    }
    return false;
}
bool OutOfJail::whenLanded(shared_ptr<Player>& p){
    cout << "Out of jail free - kept until needed" << endl;
    p->addOutOfJailCard();
    return false;
}
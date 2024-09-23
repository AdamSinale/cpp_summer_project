#include "property.hpp"
#include "player.hpp"

ostream& operator<<(ostream& os, Property& s){
    os << s.getName() << " "<< s.getPrice() <<"M";
    return os;
}

int Railroad::calculateRent(int rolled){
    int rails = 0;
    for (const auto& property : getOwner()->getProperties()) {
        if (dynamic_cast<Railroad*>(property.get())) {
            rails++;
        }
    }
    return rails*50;
}

void Street::handleOwned(){
    shared_ptr<Player> w = getOwner();
    if(numHouses==5){ cout<<"Got to your hotel"<<endl; return; }
    else{
        if((numHouses<4 && w->getBalance()<houseCost) || w->getBalance()<houseCost*4+100){ 
            cout<<"Can't buy"<<endl; return;
        }
        char ans;
        cout << "Wanna upgrade? (y/n)" << endl;
        cin >> ans;
        if(ans=='y' || ans=='Y'){ numHouses++; w->changeBalance(-price); }
    } 
}
int Street::calculateRent(int rolled){
    if(numHouses==0){ return rent; }
    else if(numHouses==5){ return hotelRent; }
    int price = houseRent;
    for(int i=1; i<numHouses; i++){ price *= 2; }
    return price;
}

#include "property.hpp"

ostream& operator<<(std::ostream& os, Property& s){
    os << s.getName() << " "<< s.getPrice() <<"M";
    return os;
}

void Railroad::handleLanding(Player& player){
    
}
int Railroad::calculateRent() const{
    return 0;
}

void Street::handleLanding(Player& player){
    
}
int Street::calculateRent() const{
    if(numHouses==0){ return rent; }
    else if(numHouses==5){ return hotelRent; }
    int price = houseRent;
    for(int i=1; i<numHouses; i++){ price *= 2; }
    return price;
}

void Utility::handleLanding(Player& player){
    
}

void Surprise::handleLanding(Player& player){
    
}
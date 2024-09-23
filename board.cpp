#include "board.hpp"


Board::Board() {
    shared_ptr<Surprise> start = make_shared<Surprise>("GO(+200 as you pass)");
    shared_ptr<Street> brown1 = make_shared<Street>("Mediter-Ranean Avenue",60,30,60,80,160);
    shared_ptr<Surprise> chest1 = make_shared<Surprise>("Community Chest");
    shared_ptr<Street> brown2 = make_shared<Street>("Baltic Avenue",60,30,60,80,160);
    shared_ptr<Surprise> tax1 = make_shared<Surprise>("Income Tax");
    shared_ptr<Railroad> rail1 = make_shared<Railroad>("Reading Railroad");
    shared_ptr<Street> cyan1 = make_shared<Street>("Oriental Avenue",100,50,100,100,200);
    shared_ptr<Surprise> chance1 = make_shared<Surprise>("Chance");
    shared_ptr<Street> cyan2 = make_shared<Street>("Vermont Avenue",100,50,100,100,200);
    shared_ptr<Street> cyan3 = make_shared<Street>("Connecticut Avenue",120,60,120,110,220);
    shared_ptr<Surprise> jail = make_shared<Surprise>("Jail");
    shared_ptr<Street> pink1 = make_shared<Street>("St. Charles Place",140,70,140,120,240);
    shared_ptr<Utility> comp1 = make_shared<Utility>("Electric Company");
    shared_ptr<Street> pink2 = make_shared<Street>("States Avenue",140,70,140,120,240);
    shared_ptr<Street> pink3 = make_shared<Street>("Virginia Avenue",160,80,160,130,260);
    shared_ptr<Railroad> rail2 = make_shared<Railroad>("Pennsylvania Railroad");
    shared_ptr<Street> orange1 = make_shared<Street>("St. James Place",180,95,180,145,190);
    shared_ptr<Surprise> chest2 = make_shared<Surprise>("Community Chest");
    shared_ptr<Street> orange2 = make_shared<Street>("Tenesse Avenue",180,95,180,145,190);
    shared_ptr<Street> orange3 = make_shared<Street>("New York Avenue",200,100,200,150,300);
    shared_ptr<Surprise> parking = make_shared<Surprise>("Free Parking");
    shared_ptr<Street> red1 = make_shared<Street>("Kentucky Avenue",220,110,220,160,320);
    shared_ptr<Surprise> chance2 = make_shared<Surprise>("Chance");
    shared_ptr<Street> red2 = make_shared<Street>("Indiana Avenue",220,110,220,160,320);
    shared_ptr<Street> red3 = make_shared<Street>("Illinois Avenue",240,120,240,170,340);
    shared_ptr<Railroad> rail3 = make_shared<Railroad>("B&O Railroad");
    shared_ptr<Street> yellow1 = make_shared<Street>("Atlanta Avenue",260,130,260,180,360);
    shared_ptr<Street> yellow2 = make_shared<Street>("Ventnor Avenue",260,130,260,180,360);
    shared_ptr<Utility> comp2 = make_shared<Utility>("Water Works");
    shared_ptr<Street> yellow3 = make_shared<Street>("Marvin Gardens",280,140,280,190,380);
    shared_ptr<Surprise> goToJail = make_shared<Surprise>("Go to jail");
    shared_ptr<Street> green1 = make_shared<Street>("Pacific Avenue",300,150,300,200,400);
    shared_ptr<Street> green2 = make_shared<Street>("North carolina Avenue",300,150,300,200,400);
    shared_ptr<Surprise> chest3 = make_shared<Surprise>("Community Chest");
    shared_ptr<Street> green3 = make_shared<Street>("Pennsylvania Avenue",320,160,320,210,420);
    shared_ptr<Railroad> rail4 = make_shared<Railroad>("Short Line");
    shared_ptr<Surprise> chance3 = make_shared<Surprise>("Chance");
    shared_ptr<Street> blue1 = make_shared<Street>("Park Place",350,175,350,225,450);
    shared_ptr<Surprise> tax2 = make_shared<Surprise>("Luxury Tax");
    shared_ptr<Street> blue2 = make_shared<Street>("Boardwalk",400,200,400,250,500);

    spaces = {start,brown1,chest1,brown2,tax1,rail1,cyan1,chance1,cyan2,cyan3,jail,pink1,comp1,pink2,pink3,rail2,orange1,chest2,orange2,orange3,
              parking,red1,chance2,red2,red3,rail3,yellow1,yellow2,comp2,yellow3,goToJail,green1,green2,chest3,green3,rail4,chance3,blue1,tax2,blue2};
}

void Board::printBoard(){
    for(size_t i=20; i<=30; i++){ cout << "|" << *spaces[i]; } cout << "|" << endl;
    size_t j = 0;
    for(size_t i=19; i>=11; i--){ 
        cout << *spaces[i] << "                " << *spaces[i+12+j] << endl; 
        j += 2;
    }
    for(size_t i=0; i<=10; i++){ cout << "|" << *spaces[i]; } cout << "|" << endl;
}


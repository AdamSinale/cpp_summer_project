#include "board.hpp"


Board::Board() {
    shared_ptr<Start> start = make_shared<Start>("GO(+200 as you pass)");
    shared_ptr<Street> brown1 = make_shared<Street>("Mediter-Ranean Avenue","brown",60,30,60,80,160);
    shared_ptr<Chest> chest1 = make_shared<Chest>("Community Chest");
    shared_ptr<Street> brown2 = make_shared<Street>("Baltic Avenue","brown",60,30,60,80,160);
    shared_ptr<Tax> tax1 = make_shared<Tax>("Income Tax");
    shared_ptr<Railroad> rail1 = make_shared<Railroad>("Reading Railroad");
    shared_ptr<Street> cyan1 = make_shared<Street>("Oriental Avenue","cyan",100,50,100,100,200);
    shared_ptr<Surprise> chance1 = make_shared<Surprise>("Chance");
    shared_ptr<Street> cyan2 = make_shared<Street>("Vermont Avenue","cyan",100,50,100,100,200);
    shared_ptr<Street> cyan3 = make_shared<Street>("Connecticut Avenue","cyan",120,60,120,110,220);
    shared_ptr<Jail> jail = make_shared<Jail>("Jail");
    shared_ptr<Street> pink1 = make_shared<Street>("St. Charles Place","pink",140,70,140,120,240);
    shared_ptr<Utility> comp1 = make_shared<Utility>("Electric Company");
    shared_ptr<Street> pink2 = make_shared<Street>("States Avenue","pink",140,70,140,120,240);
    shared_ptr<Street> pink3 = make_shared<Street>("Virginia Avenue","pink",160,80,160,130,260);
    shared_ptr<Railroad> rail2 = make_shared<Railroad>("Pennsylvania Railroad");
    shared_ptr<Street> orange1 = make_shared<Street>("St. James Place","orange",180,95,180,145,190);
    shared_ptr<Chest> chest2 = make_shared<Chest>("Community Chest");
    shared_ptr<Street> orange2 = make_shared<Street>("Tenesse Avenue","orange",180,95,180,145,190);
    shared_ptr<Street> orange3 = make_shared<Street>("New York Avenue","orange",200,100,200,150,300);
    shared_ptr<Parking> parking = make_shared<Parking>("Free Parking");
    shared_ptr<Street> red1 = make_shared<Street>("Kentucky Avenue","red",220,110,220,160,320);
    shared_ptr<Surprise> chance2 = make_shared<Surprise>("Chance");
    shared_ptr<Street> red2 = make_shared<Street>("Indiana Avenue","red",220,110,220,160,320);
    shared_ptr<Street> red3 = make_shared<Street>("Illinois Avenue","red",240,120,240,170,340);
    shared_ptr<Railroad> rail3 = make_shared<Railroad>("B&O Railroad");
    shared_ptr<Street> yellow1 = make_shared<Street>("Atlanta Avenue","yellow",260,130,260,180,360);
    shared_ptr<Street> yellow2 = make_shared<Street>("Ventnor Avenue","yellow",260,130,260,180,360);
    shared_ptr<Utility> comp2 = make_shared<Utility>("Water Works");
    shared_ptr<Street> yellow3 = make_shared<Street>("Marvin Gardens","yellow",280,140,280,190,380);
    shared_ptr<GoToJail> goToJail = make_shared<GoToJail>("Go to jail");
    shared_ptr<Street> green1 = make_shared<Street>("Pacific Avenue","green",300,150,300,200,400);
    shared_ptr<Street> green2 = make_shared<Street>("North carolina Avenue","green",300,150,300,200,400);
    shared_ptr<Chest> chest3 = make_shared<Chest>("Community Chest");
    shared_ptr<Street> green3 = make_shared<Street>("Pennsylvania Avenue","green",320,160,320,210,420);
    shared_ptr<Railroad> rail4 = make_shared<Railroad>("Short Line");
    shared_ptr<Surprise> chance3 = make_shared<Surprise>("Chance");
    shared_ptr<Street> blue1 = make_shared<Street>("Park Place","blue",350,175,350,225,450);
    shared_ptr<Tax> tax2 = make_shared<Tax>("Luxury Tax");
    shared_ptr<Street> blue2 = make_shared<Street>("Boardwalk","blue",400,200,400,250,500);

    spaces = {start,brown1,chest1,brown2,tax1,rail1,cyan1,chance1,cyan2,cyan3,jail,pink1,comp1,pink2,pink3,rail2,orange1,chest2,orange2,orange3,
              parking,red1,chance2,red2,red3,rail3,yellow1,yellow2,comp2,yellow3,goToJail,green1,green2,chest3,green3,rail4,chance3,blue1,tax2,blue2};
}

void Board::printBoard(vector<shared_ptr<Player>>& players){
    cout << "----------------------------------------------------------------";
    for(int i=0; i<spaces.size(); i++){ 
        if(i%5==0){ cout << "\n| "; }
        for(auto& p : players){ if(i==p->getPosition()){ cout << *p << " "; }}
        cout << *spaces[i] << " | ";
    }
    cout << "\n----------------------------------------------------------------" << endl;
}

int Board::jailPosition(){
    for(size_t i=0; i<spaces.size(); i++){
        if(dynamic_cast<Jail*>(spaces[i].get())){
            return i;
        }
    }
    return 0;
}
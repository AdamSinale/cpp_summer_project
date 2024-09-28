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

    brown1->addGroup({brown2}); brown2->addGroup({brown1});
    cyan1->addGroup({cyan2,cyan3}); cyan2->addGroup({cyan1,cyan3}); cyan3->addGroup({cyan1,cyan2});
    pink1->addGroup({pink2,pink3}); pink2->addGroup({pink1,pink3}); pink3->addGroup({pink1,pink2});
    orange1->addGroup({orange2,orange3}); orange2->addGroup({orange1,orange3}); orange3->addGroup({orange1,orange2});
    red1->addGroup({red2,red3}); red2->addGroup({red1,red3}); red3->addGroup({red1,red2});
    yellow1->addGroup({yellow2,yellow3}); yellow2->addGroup({yellow1,yellow3}); yellow3->addGroup({yellow1,yellow2});
    green1->addGroup({green2,green3}); green2->addGroup({green1,green3}); green3->addGroup({green1,green2});
    blue1->addGroup({blue2}); blue2->addGroup({blue1});

    tax1->addGroup({tax2}); tax2->addGroup({tax1});
    rail1->addGroup({rail2,rail3,rail4}); rail2->addGroup({rail1,rail3,rail4}); rail3->addGroup({rail2,rail1,rail4}); rail4->addGroup({rail2,rail3,rail1}); 

    spaces = {start,brown1,chest1,brown2,tax1,rail1,cyan1,chance1,cyan2,cyan3,jail,pink1,comp1,pink2,pink3,rail2,orange1,chest2,orange2,orange3,
              parking,red1,chance2,red2,red3,rail3,yellow1,yellow2,comp2,yellow3,goToJail,green1,green2,chest3,green3,rail4,chance3,blue1,tax2,blue2};
}

void Board::addSpace(shared_ptr<Property> p){ 
    spaces.push_back(p); 
    if(!dynamic_cast<Street*>(p.get())){ return; }
    vector<shared_ptr<Property>> group;
    for(auto& s : spaces){
        if(s->getColor() == p->getColor()){ 
            group.push_back(s); 
            s->addGroup({p}); 
        }
    }
    p->addGroup(group); 
}

void Board::displayBoard(sf::RenderWindow& window, const vector<shared_ptr<Player>>& players){
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        // Handle error
        return;
    }

    // Iterate over spaces to draw each property
    for (size_t i = 0; i < spaces.size(); ++i) {
        // Property shape
        sf::RectangleShape propertyShape(sf::Vector2f(170, 100));
        propertyShape.setPosition((i % 10) * 180, (i / 10) * 120);  // Grid layout
        propertyShape.setFillColor(sf::Color::White);
        propertyShape.setOutlineColor(sf::Color::Black);
        propertyShape.setOutlineThickness(2);

        window.draw(propertyShape);

        // Property name
        sf::Text propertyName(spaces[i]->getDisplay(), font, 20);
        propertyName.setPosition((i % 10) * 180 + 10, (i / 10) * 120 + 10);
        propertyName.setFillColor(sf::Color::Black); 
        window.draw(propertyName);
    }

    // Draw players
    for (const auto& player : players) {
        sf::CircleShape playerToken(15);
        playerToken.setFillColor(sf::Color::Blue);  // Use different colors for each player if desired
        int playerPosition = player->getPosition();
        playerToken.setPosition((playerPosition % 10) * 180 + 110, (playerPosition / 10) * 120 + 60);
        window.draw(playerToken);

        // Player name
        sf::Text playerName(player->getName(), font, 15);
        playerName.setPosition((playerPosition % 10) * 180 + 120, (playerPosition / 10) * 120 + 60);
        window.draw(playerName);
    }
}

int Board::jailPosition(){
    for(size_t i=0; i<spaces.size(); i++){
        if(dynamic_cast<Jail*>(spaces[i].get())){
            return i;
        }
    }
    return 0;
}
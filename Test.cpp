// ID: 322453689
// MAIL: adam.sinale@gmail.com

#include <iostream>
#include <stdexcept>
#include <vector>
#include "game.hpp"
#include "player.hpp"
#include "board.hpp"
#include "property.hpp"
#include <sstream>
#include "doctest.hpp"

using namespace std;

std::streambuf *orig = std::cout.rdbuf(); // save original buffer

void suppressOutput()
{
    std::cout.rdbuf(NULL);
}

void restoreOutput()
{
    std::cout.rdbuf(orig);
}

TEST_CASE("Test starting game")
{
    vector<string> names = {"a", "b", "c"};
    vector<vector<string>> possible_orders = {
        {"a", "b", "c"},
        {"a", "c", "b"},
        {"b", "a", "c"},
        {"b", "c", "a"},
        {"c", "b", "a"},
        {"c", "a", "b"}
    };

    std::istringstream input("a\nb\nc\n");   // input to game's names
    std::cin.rdbuf(input.rdbuf());
    suppressOutput();
    Game game(3);
    restoreOutput();

    vector<shared_ptr<Player>>& ps = game.getPlayers();
    vector<string> result_names;
    for (const auto& player : ps) {
        result_names.push_back(player->getName());
    }
    bool valid_order = false;
    for (const auto& order : possible_orders) {
        if (result_names == order) {
            valid_order = true;
            break;
        }
    }
    CHECK(valid_order);                            // players correctly set

}
TEST_CASE("Test game pass start")
{
    std::istringstream input("a\nb\nc\n");  
    std::cin.rdbuf(input.rdbuf());
    suppressOutput();
    Game game(3);
    restoreOutput();
    
    vector<shared_ptr<Player>>& ps = game.getPlayers();
    ps[0]->setPosition(35);
    CHECK(ps[0]->getBalance() == 1500);
    game.passStartAction(ps[0],5,5);
    CHECK(ps[0]->getBalance() == 1700);
}
TEST_CASE("Test game move")
{
    std::istringstream input("a\nb\nc\n");  
    std::cin.rdbuf(input.rdbuf());
    suppressOutput();
    Game game(3);
    restoreOutput();
    
    vector<shared_ptr<Player>>& ps = game.getPlayers();
    CHECK(ps[0]->getPosition() == 0);
    CHECK(ps[0]->getBalance() == 1500);
    game.movePlayer(ps[0],2,2);
    CHECK(ps[0]->getPosition() == 4);
    CHECK(ps[0]->getBalance() == 1400);    // 4 is tax
    ps[0]->changeBalance(-2000);           // bankrupt to show he is removed
    game.movePlayer(ps[0],1,1);
    CHECK(game.getPlayers().size() == 2);  // removed

}
TEST_CASE("Test game jail")
{
    std::istringstream input("a\nb\nc\n");  
    std::cin.rdbuf(input.rdbuf());
    suppressOutput();
    Game game(3);
    restoreOutput();
    
    vector<shared_ptr<Player>>& ps = game.getPlayers();
    CHECK(ps[0]->isInJail() == false);
    game.sendToJail(ps[0]);
    CHECK(ps[0]->isInJail() == true);
    game.jailAction(ps[0],6,6);              // double
    CHECK(ps[0]->isInJail() == false);

    game.sendToJail(ps[0]);
    ps[0]->addOutOfJailCard();
    CHECK(ps[0]->getOutOfJailCards() == 1);
    std::istringstream input2("y\n");  
    std::cin.rdbuf(input2.rdbuf());
    game.jailAction(ps[0],5,6);              // out of jail card
    restoreOutput();
    CHECK(ps[0]->getOutOfJailCards() == 0);
    CHECK(ps[0]->isInJail() == false);
    
    game.sendToJail(ps[0]);
    std::istringstream input3("y\n");  
    std::cin.rdbuf(input3.rdbuf());
    game.jailAction(ps[0],5,6);              // paid 50
    restoreOutput();
    CHECK(ps[0]->getBalance() == 1450);
    CHECK(ps[0]->isInJail() == false);
    
}
TEST_CASE("Test ending game")
{
    std::istringstream input("a\nb\nc\n");  
    std::cin.rdbuf(input.rdbuf());
    suppressOutput();
    Game game(3);
    restoreOutput();
    
    vector<shared_ptr<Player>>& ps = game.getPlayers();

    CHECK(game.gameEnded() == false);
    ps[0]->changeBalance(2500);
    CHECK(game.gameEnded() == true);          // p[0] got to 4000
    ps[0]->changeBalance(-1500);
    CHECK(game.gameEnded() == false); 

    std::istringstream input2("a\n");  
    std::cin.rdbuf(input2.rdbuf());
    suppressOutput();
    Game game2(1);
    restoreOutput(); // in game, every move it is check that players arent bankrupt and if so removes them 
    CHECK(game2.gameEnded() == true);          // so we will just check a game with 1 player remains
}

TEST_CASE("Test player")
{
    Player p1("a");
    CHECK(p1.getName() == "a");
    
    CHECK(p1.getBalance() == 1500);   // balance handling
    p1.changeBalance(-500);
    CHECK(p1.getBalance() == 1000);
    p1.changeBalance(500);
    CHECK(p1.getBalance() == 1500);

    CHECK(p1.getPosition() == 0);    // start at beggining
    p1.setPosition(30);
    CHECK(p1.getPosition() == 30);
    p1.setPosition(-1);              // not allowing smaller than 0
    CHECK(p1.getPosition() == 0);
    p1.setPosition(30);
    p1.move(5,40);
    CHECK(p1.getPosition() == 35);  // moved 5
    p1.move(5,40);
    CHECK(p1.getPosition() == 0);   // moved 5 but starts new cycle

    CHECK(p1.getProperties().size()==0);  // starting with 0 property
    shared_ptr<Property> s = make_shared<Street>("s","red",1,1,1,1,1);
    p1.addProperty(s);
    CHECK(p1.getProperties().size()==1);  // added one street

    CHECK(p1.getRolled() == 0);      // check dices rolled each turn
    p1.setRolled(10);
    CHECK(p1.getRolled() == 10);

    CHECK(p1.getOutOfJailCards() == 0);  // out of jail cards
    p1.addOutOfJailCard();
    CHECK(p1.getOutOfJailCards() == 1);
    p1.useOutOfJailCard();
    CHECK(p1.getOutOfJailCards() == 0);
    
    CHECK(p1.isInJail() == false);        // in and out of jail handling
    p1.goToJail();
    CHECK(p1.isInJail() == true);
    p1.outOfJail();
    CHECK(p1.isInJail() == false);
    p1.goToJail();
    p1.jailTurn(); p1.jailTurn(); p1.jailTurn();
    CHECK(p1.isInJail() == false);
    p1.goToJail();
    p1.useOutOfJailCard();
    CHECK(p1.isInJail() == false);
    
    CHECK(p1.isBankrupt() == false);
    p1.changeBalance(-1500);
    CHECK(p1.isBankrupt() == true);
}

TEST_CASE("Test board")
{
    shared_ptr<Board> board = make_shared<Board>();
    CHECK(board->boardSize() == 40);          // initially
    shared_ptr<Property> s = make_shared<Street>("s","red",1,1,1,1,1);
    board->addSpace(s);
    CHECK(board->boardSize() == 41);          // added one
    CHECK(board->getProperty(40) == s);       // check added space right
    CHECK(board->jailPosition() == 10);        // initially jail is at 9 (important for board changes for dynamic)
}

TEST_CASE("Test property - street")
{
    shared_ptr<Player> p1 = make_shared<Player>("a");
    shared_ptr<Player> p2 = make_shared<Player>("b");

    shared_ptr<Street> s = make_shared<Street>("s","red",1,2,3,4,5);
    CHECK(s->getName() == "s");
    CHECK(s->getColor() == "red");
    CHECK(s->getPrice() == 1);
    CHECK(s->getNumHouses() == 0);
    CHECK(s->calculateRent() == 2);     // because no houses so rent
    s->addHouse();
    CHECK(s->calculateRent() == 4);     // houses rent
    s->addHouse();
    CHECK(s->calculateRent() == 8);     // 2 houses rent
    s->addHouse(); s->addHouse(); s->addHouse();
    CHECK(s->calculateRent() == 5);     // hotel rent
    CHECK(s->getOwner() == nullptr);    

    std::istringstream input("y");  
    std::cin.rdbuf(input.rdbuf());
    suppressOutput();
    s->whenLanded(p1);                      // no owner so p1 buys
    restoreOutput();
    CHECK(s->getOwner() == p1);             // new owner
    CHECK(p1->getBalance() == 1499);        // he paid
    s->whenLanded(p2);                      // p2 pays rent
    CHECK(p2->getBalance() == 1500-s->calculateRent());
    std::istringstream input2("y");  
    std::cin.rdbuf(input2.rdbuf());
    suppressOutput();
    s->whenLanded(p1);                      // p1 upgrades
    restoreOutput();
    CHECK(s->getOwner() == p1);             // new owner
}
TEST_CASE("Test property - railroad")
{
    shared_ptr<Player> p1 = make_shared<Player>("a");
    shared_ptr<Player> p2 = make_shared<Player>("b");

    shared_ptr<Railroad> r1 = make_shared<Railroad>("r1");
    shared_ptr<Railroad> r2 = make_shared<Railroad>("r2");
    CHECK(r1->getName() == "r1");
    CHECK(r1->getPrice() == 200);
    CHECK(r1->getOwner() == nullptr);
    r1->setOwner(p1);
    p1->addProperty(r1);
    CHECK(r1->getOwner() == p1);
    CHECK(r1->calculateRent() == 50);     // 1 railroad
    r2->setOwner(p1);
    p1->addProperty(r2);
    CHECK(r1->calculateRent() == 100);    // 2 railroads

    r1->whenLanded(p2);                   // p2 pays rent
    CHECK(p2->getBalance() == 1500-r1->calculateRent());
    r1->whenLanded(p1);                   // nothing if landed again
}
TEST_CASE("Test property - utility")
{
    shared_ptr<Player> p1 = make_shared<Player>("a");
    shared_ptr<Player> p2 = make_shared<Player>("b");

    shared_ptr<Utility> u = make_shared<Utility>("u");
    CHECK(u->getName() == "u");
    CHECK(u->getPrice() == 150);
    CHECK(u->getOwner() == nullptr);
    u->setOwner(p1);
    p1->addProperty(u);
    CHECK(u->getOwner() == p1);

    CHECK(u->calculateRent(5) == 5*10);   // 10 * rolled amount
    p2->setRolled(12);
    u->whenLanded(p2);                   // p2 pays rent
    CHECK(p2->getBalance() == 1500-12*10);
    u->whenLanded(p1);                   // nothing if landed again
}
TEST_CASE("Test property - Chest")
{
    shared_ptr<Player> p = make_shared<Player>("a");
    shared_ptr<Chest> c = make_shared<Chest>("c");
    int before = p->getBalance();
    c->whenLanded(p);
    CHECK(p->getBalance() >= before+100);
    CHECK(p->getBalance() <= before+400);
}
TEST_CASE("Test property - Start")
{
    shared_ptr<Player> p = make_shared<Player>("a");
    shared_ptr<Start> s = make_shared<Start>("s");
    int before = p->getBalance();
    s->whenLanded(p);
    CHECK(p->getBalance() == before+200);             // 200 for passing, 200 for landing (here only landing)
}
// nothing to test for Parking or Jail
TEST_CASE("Test property - Tax")
{
    shared_ptr<Player> p = make_shared<Player>("a");
    shared_ptr<Tax> t = make_shared<Tax>("t");
    int before = p->getBalance();
    t->whenLanded(p);
    CHECK(p->getBalance() == before-100);
}
TEST_CASE("Test property - GoToJail")
{
    shared_ptr<Player> p = make_shared<Player>("a");
    shared_ptr<GoToJail> gtj = make_shared<GoToJail>("gtj");
    CHECK(p->isInJail() == false);
    gtj->whenLanded(p);
    CHECK(p->isInJail() == true);
}
// Surprise just runs random of the following
TEST_CASE("Test property - Get50")
{
    shared_ptr<Player> p = make_shared<Player>("a");
    shared_ptr<Get50> g50 = make_shared<Get50>("g50");
    int before = p->getBalance();
    g50->whenLanded(p);
    CHECK(p->getBalance() == before+50);
}
TEST_CASE("Test property - Back3Steps")
{
    shared_ptr<Player> p = make_shared<Player>("a");
    shared_ptr<Back3Steps> b3 = make_shared<Back3Steps>("b3");
    p->setPosition(4);
    b3->whenLanded(p);
    CHECK(p->getPosition() == 1);
    b3->whenLanded(p);
    CHECK(p->getPosition() == 0);    // no minuses - go to 0 minimum
}
TEST_CASE("Test property - Back3Steps")
{
    shared_ptr<Player> p = make_shared<Player>("a");
    shared_ptr<Street> s = make_shared<Street>("s","red",1,2,3,4,5);
    p->addProperty(s);

    shared_ptr<Repair> r = make_shared<Repair>("r");
    r->whenLanded(p);
    CHECK(p->getBalance() == 1500);      // no houses
    s->addHouse();
    r->whenLanded(p);
    CHECK(p->getBalance() == 1500-25);   // 1 house
    s->addHouse(); s->addHouse(); s->addHouse(); s->addHouse();
    r->whenLanded(p);
    CHECK(p->getBalance() == 1500-25-100);   // -25 from before, 1 hotel
}
TEST_CASE("Test property - OutOfJail")
{
    shared_ptr<Player> p = make_shared<Player>("a");
    shared_ptr<OutOfJail> ooj = make_shared<OutOfJail>("ooj");

    CHECK(p->getOutOfJailCards() == 0); 
    ooj->whenLanded(p);
    CHECK(p->getOutOfJailCards() == 1); 
}

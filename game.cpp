#include "game.hpp"

Game::Game(int pa){
    this->board = make_shared<Board>();
    this->turn = 0;
    string name;
    for(int i=0; i<pa; i++){
        cout << "Players name (order doesn't matter, i'll shuffle)" << endl;
        cin >> name;
        this->players.push_back(make_shared<Player>(name));
    }
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    shuffle(players.begin(), players.end(), std::default_random_engine(seed));
    cout << "The starting player is " << players[turn]->getName() << "\n" << endl;
}

bool Game::jailAction(shared_ptr<Player>& p, int r1, int r2){
    if(p->isInJail()){ 
        cout << "Still in jail, let's roll the dice" << endl;
        if(r1==r2){ 
            cout << "Released from jail!" << endl;
            p->outOfJail();
            return true;
        }
        else if(p->getOutOfJailCards() > 0){
            char ans;
            cout << "Want to use out of jail card? (y/n)" << endl;
            cin >> ans;
            if(ans=='y' || ans=='Y'){ 
                p->useOutOfJailCard();
                p->outOfJail(); 
                return true; 
            }
        }
        else if(p->getBalance() >= 50){ 
            char ans;
            cout << "Want to pay out? (y/n)" << endl;
            cin >> ans;
            if(ans=='y' || ans=='Y'){ 
                p->changeBalance(-50);
                p->outOfJail(); 
                return true; 
            }
        }
        p->jailTurn(); 
        if(!p->isInJail()){ p->changeBalance(-50); }
        return true; 
    } return false;
}

void addSpace(){
    
}

void Game::movePlayer(shared_ptr<Player>& p, int r1, int r2){
    if(jailAction(p,r1,r2)){ return; }
    p->setRolled(r1+r2);
    passStartAction(p,r1,r2);
    p->move(r1+r2,board->boardSize());
    cout << "You're now at " << p->getPosition() << endl;
    shared_ptr<Property> curPos = board->getProperty(p->getPosition());
    if(curPos->whenLanded(p)){ p->addProperty(curPos); }
    if(p->isBankrupt()){ players.erase(std::remove(players.begin(),players.end(),p),players.end()); }
}
int Game::rollDice(){
    static int previous = 0; 
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 6);
    int current;
    do {
        current = dist(gen);
    } while (current == previous);
    previous = current; 
    return current;
}

void Game::passStartAction(shared_ptr<Player>& p, int r1, int r2){
    if(p->getPosition()+r1+r2 >= board->boardSize()){     
        p->changeBalance(200);
        cout << "Passed start point, +200" << endl;
    }
}
bool Game::gameEnded() const{
    if(players.size() == 1){
        cout << players[0]->getName() << " WON!!" << endl;
        return true;
    }
    for(size_t i=0; i<players.size(); i++) {
        if(players[i]->getBalance() >= 4000){ 
            cout << players[i]->getName() << " WON!!" << endl;
            return true;
        }
    }   
    return false;
}

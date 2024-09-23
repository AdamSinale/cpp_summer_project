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
void Game::movePlayer(shared_ptr<Player>& p, int rolled){
    if(p->getPosition()+rolled >= board->boardSize()){ 
        p->changeBalance(200);
        cout << "Passed start point, +200" << endl;
    }
    p->move(rolled,board->boardSize());
    cout << "You're now at " << p->getPosition() << endl;
    shared_ptr<Property> curPos = board->getProperty(p->getPosition());
}
int Game::rollDice(){
    srand(time(0));
    int result = (rand() % 6 + 1) + (rand() % 6 + 1);
    
    return result;
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
}
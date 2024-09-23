#include "player.hpp"
#include "game.hpp"
#include "property.hpp"


int main() {
    int playerAmount;
    cout << "How many players will play? (2-8)" << endl;
    cin >> playerAmount;
    while(playerAmount < 2 || playerAmount >8){ 
        cout << "2-8 !!!" << endl;
        cin >> playerAmount;
    }
    Game game(playerAmount);
    vector<shared_ptr<Player>> players = game.getPlayers();
    game.printBoard();

    int rolled;
    while(!game.gameEnded()){
        cout << "Your turn " << players[game.getTurn()] << endl;
        rolled = game.rollDice();
        cout << "You rolled" << rolled << endl;
        game.movePlayer(players[game.getTurn()],rolled);
        
        game.nextTurn();
    }
}

// 6 7 1 2 2 1 3 1 2 3 3 1 4 5 1 5 3 1 6 1 5 6 1 k
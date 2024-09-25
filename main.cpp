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
    vector<shared_ptr<Player>>& players = game.getPlayers();
    game.printBoard();

    char ans;
    cout << "***** Wish to add a Space first? (y/n) *****" << endl;
    cin >> ans;
    if(ans=='y' || ans=='Y'){ game.addSpace(); }
    int r1,r2,times=0;
    while(!game.gameEnded()){
        cout << "--------------------------------"  << endl;
        times++;
        if(times==4){                                              // 4th turn due to 3 doubles 
            cout << "3 doubles in a row! jail" << endl;
            game.sendToJail(players[game.getTurn()]);
            times=0; 
            game.nextTurn();
            continue; 
        }
        cout << "Your turn " << *players[game.getTurn()] << endl;
        r1 = game.rollDice();
        r2 = game.rollDice();
        cout << "You rolled " << r1<<","<<r2 << endl;
        game.movePlayer(players[game.getTurn()],r1,r2);

        if(r1!=r2){ game.nextTurn(); times=0; }
    }
}

// 8 a b c d e f g h y 5 boo! 
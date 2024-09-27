
#ifndef GAME_HPP
#define GAME_HPP

#include "board.hpp"
#include "player.hpp"

class Game {
    vector<shared_ptr<Player>> players;
    shared_ptr<Board> board;
    int turn = 0;
public:
    Game(int pa);
    void displayBoard(sf::RenderWindow& window){ board->displayBoard(window,players); }
    void addSpace();
    vector<shared_ptr<Player>>& getPlayers(){ return players; }
    void nextTurn(){ turn = (turn+1) % players.size(); };
    void movePlayer(shared_ptr<Player>& p, int r1, int r2);
    void sendToJail(shared_ptr<Player>& p);
    bool jailAction(shared_ptr<Player>& p, int r1, int r2);
    void passStartAction(shared_ptr<Player>& p, int r1, int r2);
    int getTurn(){ return turn;};
    bool gameEnded() const;
    int rollDice();
};

#endif

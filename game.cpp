
// game.cpp

#include <iostream>
#include "catan.hpp"

int main() {
    Catan play;
    play.startGame();
    Player *winner = nullptr;
    while (true)
    {
        for(size_t i=0; i<play.players.size(); i++) {
            play.turn(play.players[i]);
            winner = play.checkWin();
            if(winner!=nullptr) {break;}
        }
            if(winner!=nullptr) {break;}
    }

    cout << "end of the game the winner is: " << winner->getName() << endl;
    cout << "************************************************" << endl;
    cout << "                SCORE BOARD:                    " << endl;
    cout << "************************************************" << endl;
    cout << "player: " << play.players[0]->getName() << " with " << play.players[0]->getPoints() << " points" << endl;  
    cout << "player: " << play.players[1]->getName() << " with " << play.players[1]->getPoints() << " points" << endl;  
    cout << "player: " << play.players[2]->getName() << " with " << play.players[2]->getPoints() << " points" << endl;  
    cout << "************************************************" << endl;
    
    return 0;
}
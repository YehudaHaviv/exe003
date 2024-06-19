
//catan.hpp

#ifndef CATAN_HPP
#define CATAN_HPP

#include <iostream>
#include <vector>
#include "board.hpp"
#include "player.hpp"


using namespace std;


    class Catan {

        private:

            static int maxRoad;
            static Player* maxRoadPlayer;

            static int maxArmy;
            static Player* maxArmyPlayer;

            void checkLongestRoad();
            void checkBigestArmy();

            size_t UpdateUserYtoMap(size_t y); //the x will stay the same

        public:
            Board board; 
            vector<Player*> players;

            Catan();
            ~Catan();

            void startGame();

            void turn(Player *p);

            void useingCard(Player *p);

            Player* checkWin();


    };



#endif
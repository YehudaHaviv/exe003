
// board.hpp

#ifndef BOARD_HPP
#define BOARD_HPP

#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include "player.hpp"
#include "vertex.hpp"

using namespace std;

class Board {

    private:
        vector<Tile*> tiles;
        vector<vector<Vertex*>> vertexes;
        vector<Edge*> edges;
       
        void initializeTiles();
        void initializeVertex();
        void initializeEdge();

        void ColorEdgeByPlayer(Player *p, Edge* e);
        void ColorVertexByPlayer(Player *p);
        string middleStringReplac(string middle, string insert);
        string middleIntReplace(string middle, int num);
        string middlePirate(string middle);

    public:

         /*14 knight 6 progress 5 victory point*/
        static vector<Cards> cards;


        Board();
        bool startPlaceingSattelment(Player *p, size_t x, size_t y);
        bool startPlacingRoad(Player *p, size_t x1, size_t y1, size_t x2, size_t y2);
        bool placeSattelment(Player *p, size_t x, size_t y);
        bool placeRoad(Player *p, size_t x1, size_t y1, size_t x2, size_t y2);
        bool placeCity(Player *p, size_t x, size_t y);
        bool buyCard(Player *p);
        void handleRollDice(int roll);
        void handelRobber(Player *p);
        void steel(Player *p, Player *s);
        void printBoard();


};

#endif
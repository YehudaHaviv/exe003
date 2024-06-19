
// player.hpp

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <iostream>
#include <string>
#include <vector>
#include <random>
#include "tile.hpp"
#include "edge.hpp"


enum class Cards {
    victoryPoint, 
    Knight, 
    roadBuilding,
    YearOfPlenty, 
    monopoly
};


using namespace std;


class Player {

    private:
        string color;
        string name;
        vector<Cards> CardsToUse;
        vector<Cards> CardToNextTurn;
        vector<TileType> Resource;
        vector<Vertex*> places;
        vector<Edge*> road;
        int points;
        int numberOfraod;
        int army;



    public:

        // constractor
        Player(string name, string color); 
        
        // getter
        string getColor();
        string getName();
        vector<TileType>* getResource();
        int getPoints();
        int getArmy();     
        int getNumberOfRoads();
        vector<Cards> getCardToUse();

        // add and remove points
        void addPoint();
        void removePoint();

        // dice roll
        int rollDice();

        // resource handle
        bool addResource(TileType Resource);
        bool removeResource(TileType resource);
        
        bool checkResourceToSattelment();
        bool checkResourceToRoad();
        bool checkResourceToCard();
        bool checkResourceTocity(); 
        
        // check player point > 9 
        bool checkWin();
        
        // add first sattelments
        void addFirstSattelment(Vertex* v);
        bool addFristRoad(Edge* e);

        // add sattelment or road
        bool addSattelment(Vertex* v);
        bool addRoad(Edge* e);

        // add by one to road or army
        void addtoroad();
        void addtoarmy();  

        // buy and use card
        bool buyCard(Cards c);
        int useCard();

        void endturnMoveCards();
        
};

#endif
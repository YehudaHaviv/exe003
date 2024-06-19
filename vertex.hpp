
//vertex.hpp

#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <iostream>

class Player;

using namespace std;

class Vertex {

    private:
        size_t x;
        size_t y;
        Player* owner = nullptr;
        bool sattelment;
        bool city;

    public:
        Vertex(size_t x, size_t y);
        size_t getX(); // return x cor...
        size_t getY(); // return y cor...
        Player* getOwner(); // if null then free else return player owner
        void setSattelment(Player *p); // set place and owner
        bool IsCity(); // 
        void SetCity();
        string printV();
};

#endif
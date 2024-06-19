
// tile.hpp

#ifndef TILE_H
#define TILE_H

#include <iostream>
#include <random>
#include <vector>
#include <string>

class Vertex;

using namespace std;

enum class TileType
{
    NONE,
    WOOD,
    LEAD,
    SHEEP,
    WHEAT,
    BRICK,
    DESERT,
};

class Tile
{

private:

    int numberToken; // number tile for dice roll
    TileType Type; // type of tile
    bool Robber; // True if there is a robber
    vector<Vertex*> vertex;


public:
    Tile(TileType type, vector<Vertex*> vertex, int num); // constractor 
    int getNumberToken(); // return number in the tile
    TileType getResourceType() const; // return type
    vector<Vertex*> getVertex();
    bool hasRobber(); // true if there is a robber
    void setRobberToTrue(); // change robber to this tile or to diffrent tile
    void setRobberToFalse(); // change robber to this tile or to diffrent tile
    string tileTypeToString(const TileType& tileType); // return string type of tile 
    string tileToString();
};

#endif // TILE_H


// tile.cpp

#include "tile.hpp" 

using namespace std;


Tile::Tile(TileType type, vector<Vertex*> vertex, int num) {
    this->numberToken = num;
    this->Type = type;
    this->Robber = false;
    if(this->Type==TileType::DESERT) {
        this->Robber = true;
    }
    this->vertex = vertex;
} 


vector<Vertex*> Tile::getVertex() {return this->vertex;}

    int Tile::getNumberToken() {return this->numberToken;}
    TileType Tile::getResourceType() const {return this->Type;}
    bool Tile::hasRobber() {return this->Robber;}
    void Tile::setRobberToTrue() {this->Robber = true;}
    void Tile::setRobberToFalse() {this->Robber = false;}


string Tile::tileTypeToString(const TileType& tileType) {
        switch (tileType) {
            case TileType::WOOD:
                return "wood";
            case TileType::BRICK:
                return "brick";
            case TileType::DESERT:
                return "desert";
            case TileType::WHEAT:
                return "weat";
            case TileType::LEAD:
                return "lead";
            case TileType::SHEEP:
                return "sheep";
            default:
                return "None";
        }
}

string Tile::tileToString() {
    string ans = this->tileTypeToString(this->Type);
    return ans;
}
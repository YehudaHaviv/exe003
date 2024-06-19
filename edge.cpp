
//edge.cpp

#include "edge.hpp"

using namespace std;


Edge::Edge(Vertex* one, Vertex* two, const string& e) {
    this->vertexs = make_pair(one, two);
    this->road = false;
    this->look = e;
    this->owner = nullptr;
}

pair<Vertex*,Vertex*> Edge::getVertexs() {
    return this->vertexs;
}
        
bool Edge::IsRoad() {
    return this->road;
}
    
void Edge::setRoad(Player* p) {
    this->owner = p;
    this->road = true;
}

string Edge::getEdge() {
    return this->look;
}

Player* Edge::getOwner() {
    return this->owner;
}
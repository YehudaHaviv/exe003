
//vertex.cpp

#include "vertex.hpp"

using namespace std;

Vertex::Vertex(size_t x, size_t y) {
    this->x = x;
    this->y = y;
    this->owner = nullptr;
    this->city = false;
    this->sattelment = false;
}

size_t Vertex::getX() {return this->x;}

size_t Vertex::getY() {return this->y;}

Player* Vertex::getOwner() {return this->owner;}

void Vertex::setSattelment(Player *p) {
    this->owner = p;    
    this->sattelment = true;
}

bool Vertex::IsCity() {return this->city;}

void Vertex::SetCity() {
    this->sattelment =false;
    this->city = true;
}

string Vertex::printV() {
    string ans = "💲";
    if(this->sattelment) {ans = "🏠";}
    if(this->IsCity()) {ans = "🏢";}
    return ans;
}    

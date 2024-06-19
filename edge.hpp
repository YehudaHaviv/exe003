
//edge.hpp

#include <iostream>


class Vertex;
class Player;

using namespace std;


class Edge {
    
    private:
        pair<Vertex*,Vertex*> vertexs;
        Player* owner;
        string look;
        bool road;

    public:
        Edge(Vertex *one, Vertex *two, const string& e);
        pair<Vertex*,Vertex*> getVertexs();
        bool IsRoad();
        void setRoad(Player *p);
        string getEdge();
        Player* getOwner();
};
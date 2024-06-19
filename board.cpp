
// board.cpp

#include "board.hpp"

using namespace std;

const string RESET = "\033[0m";
const string RED = "\033[1;31m";
const string GREEN = "\033[32m";
const string BLUE = "\033[34m";
const string YELLOW = "\033[33m";
const string ERASE = "\033[2K\r";

vector<Cards> Board::cards;

const int board_width = 11;
const int board_height = 6;

Board::Board()
{
    Board::cards = {
        Cards::Knight, Cards::Knight, Cards::Knight, Cards::Knight, Cards::Knight, Cards::Knight,
        Cards::Knight, Cards::Knight, Cards::Knight, Cards::Knight, Cards::Knight, Cards::Knight, Cards::Knight, Cards::Knight,
        Cards::victoryPoint, Cards::victoryPoint, Cards::victoryPoint, Cards::victoryPoint, Cards::victoryPoint,
        Cards::monopoly, Cards::monopoly, Cards::roadBuilding, Cards::roadBuilding, Cards::YearOfPlenty, Cards::YearOfPlenty};
    shuffle(cards.begin(), cards.end(), random_device());

    initializeVertex();
    initializeEdge();
    initializeTiles();
}

void Board::initializeVertex()
{
    for (size_t y = 0; y < 6; y++)
    {
        vector<Vertex *> v;
        for (size_t x = 0; x < 11; x++)
        {
            if ((x == 0 && (y == 0 || y == 1 || y == 4 || y == 5)) || (x == 1 && (y == 0 || y == 5)) || (x == 9 && (y == 0 || y == 5)) || (x == 10 && (y == 0 || y == 1 || y == 4 || y == 5)))
            {
                v.push_back(nullptr);
            }
            else
            {
                v.push_back(new Vertex(x, y));
            }
        }
        this->vertexes.push_back(v);
    }
}

void Board::initializeEdge()
{
    for (size_t y = 0; y < 6; y++)
    {
        for (size_t x = 0; x < 11; x++)
        {
            if (x + 1 < 11 && this->vertexes[y][x] != nullptr && this->vertexes[y][x + 1] != nullptr)
            {
                string e1 = "";
                if (y % 2 == 0)
                {
                    if (x % 2 == 0)
                    {
                        e1 = "//";
                    }
                    else
                    {
                        e1 = "\\\\";
                    }
                }
                else
                {
                    if (x % 2 == 0)
                    {
                        e1 = "\\\\";
                    }
                    else
                    {
                        e1 = "//";
                    }
                }
                this->edges.push_back(new Edge(this->vertexes[y][x], this->vertexes[y][x + 1], e1));
            }
        }
        for (size_t x = 0; x < 11; x++)
        {
            if (y + 1 < 6 && this->vertexes[y][x] != nullptr && this->vertexes[y + 1][x] != nullptr)
            {
                if ((x % 2 == 0 && y % 2 == 0) || (x % 2 == 1 && y % 2 == 1))
                {
                    string e1 = "||";
                    this->edges.push_back(new Edge(this->vertexes[y][x], this->vertexes[y + 1][x], e1));
                }
            }
        }
    }
}

void Board::initializeTiles()
{
    vector<TileType> resources = {
        TileType::SHEEP, TileType::SHEEP, TileType::SHEEP, TileType::SHEEP,
        TileType::WHEAT, TileType::WHEAT, TileType::WHEAT, TileType::WHEAT, TileType::BRICK, TileType::BRICK,
        TileType::BRICK, TileType::LEAD, TileType::LEAD, TileType::LEAD, TileType::WOOD,
        TileType::WOOD, TileType::WOOD, TileType::WOOD, TileType::DESERT};
    vector<size_t> diceNumbers = {2, 3, 3, 4, 4, 5, 5, 6, 6, 8, 8, 9, 9, 10, 10, 11, 11, 12};

    shuffle(resources.begin(), resources.end(), random_device());
    shuffle(diceNumbers.begin(), diceNumbers.end(), random_device());

    vector<vector<Vertex *>> verticesList = {
        {vertexes[0][2], vertexes[0][3], vertexes[0][4], vertexes[1][2], vertexes[1][3], vertexes[1][4]},
        {vertexes[0][4], vertexes[0][5], vertexes[0][6], vertexes[1][4], vertexes[1][5], vertexes[1][6]},
        {vertexes[0][6], vertexes[0][7], vertexes[0][8], vertexes[1][6], vertexes[1][7], vertexes[1][8]},
        {vertexes[1][1], vertexes[1][2], vertexes[1][3], vertexes[2][1], vertexes[2][2], vertexes[2][3]},
        {vertexes[1][3], vertexes[1][4], vertexes[1][5], vertexes[2][3], vertexes[2][4], vertexes[2][5]},
        {vertexes[1][5], vertexes[1][6], vertexes[1][7], vertexes[2][5], vertexes[2][6], vertexes[2][7]},
        {vertexes[1][7], vertexes[1][8], vertexes[1][9], vertexes[2][7], vertexes[2][8], vertexes[2][9]},
        {vertexes[2][0], vertexes[2][1], vertexes[2][2], vertexes[3][0], vertexes[3][1], vertexes[3][2]},
        {vertexes[2][2], vertexes[2][3], vertexes[2][4], vertexes[3][2], vertexes[3][3], vertexes[3][4]},
        {vertexes[2][4], vertexes[2][5], vertexes[2][6], vertexes[3][4], vertexes[3][5], vertexes[3][6]},
        {vertexes[2][6], vertexes[2][7], vertexes[2][8], vertexes[3][6], vertexes[3][7], vertexes[3][8]},
        {vertexes[2][8], vertexes[2][9], vertexes[2][10], vertexes[3][8], vertexes[3][9], vertexes[3][10]},
        {vertexes[3][1], vertexes[3][2], vertexes[3][3], vertexes[4][1], vertexes[4][2], vertexes[4][3]},
        {vertexes[3][3], vertexes[3][4], vertexes[3][5], vertexes[4][3], vertexes[4][4], vertexes[4][5]},
        {vertexes[3][5], vertexes[3][6], vertexes[3][7], vertexes[4][5], vertexes[4][6], vertexes[4][7]},
        {vertexes[3][7], vertexes[3][8], vertexes[3][9], vertexes[4][7], vertexes[4][8], vertexes[4][9]},
        {vertexes[4][2], vertexes[4][3], vertexes[4][4], vertexes[5][2], vertexes[5][3], vertexes[5][4]},
        {vertexes[4][4], vertexes[4][5], vertexes[4][6], vertexes[5][4], vertexes[5][5], vertexes[5][6]},
        {vertexes[4][6], vertexes[4][7], vertexes[4][8], vertexes[5][6], vertexes[5][7], vertexes[5][8]}};

    int indexD, indexR = 0;
    for (auto &vertices : verticesList)
    {
        TileType type = resources[indexR];
        if (type != TileType::DESERT)
        {
            tiles.emplace_back(new Tile(type, vertices, diceNumbers[indexD]));
        }
        else
        {
            tiles.emplace_back(new Tile(type, vertices, 0));
            indexD--;
        }
        indexR++;
        indexD++;
    }
}

bool Board::startPlaceingSattelment(Player *p, size_t x, size_t y)
{
    if (x > 10)
    {
        return false;
    }
    if (y > 5)
    {
        return false;
    }
    for (size_t i = 0; i < 6; i++)
    {
        for (size_t j = 0; j < 11; j++)
        {
            if (vertexes[i][j] != nullptr)
            {
                if (vertexes[i][j]->getX() == x && vertexes[i][j]->getY() == y)
                {
                    if ((((x % 2 == 0 && y % 2 == 0) || (x % 2 == 1 && y % 2 == 1))&&
                        (i+1<6 && vertexes[i + 1][j] != nullptr && vertexes[i + 1][j]->getOwner() != nullptr)) ||
                        (((x % 2 == 1 && y % 2 == 0) || (x % 2 == 0 && y % 2 == 1)) &&
                        (i != 0 && vertexes[i - 1][j] != nullptr && vertexes[i - 1][j]->getOwner() != nullptr)) ||
                        (j+1<11 && vertexes[i][j + 1] != nullptr && vertexes[i][j + 1]->getOwner() != nullptr) ||
                        (j != 0 && vertexes[i][j - 1] != nullptr && vertexes[i][j - 1]->getOwner() != nullptr))
                    {
                        cout << "cant place sattelment here with sattelment near by\n";
                        return false;
                    }
                    else
                    {
                        if (vertexes[i][j]->getOwner() == nullptr)
                        {
                            p->addPoint();
                            vertexes[i][j]->setSattelment(p);
                            p->addFirstSattelment(vertexes[i][j]);
                            return true;
                        }
                        else
                        {
                            cout << "this place is taken allready\n";
                            return false;
                        }
                    }
                }
            }
        }
    }
    return false;
}

bool Board::startPlacingRoad(Player *p, size_t x1, size_t y1, size_t x2, size_t y2)
{
    if (x1 > 10)
    {
        return false;
    }
    if (y1 > 5)
    {
        return false;
    }
    if (x2 > 10)
    {
        return false;
    }
    if (y2 > 5)
    {
        return false;
    }
    for (size_t i = 0; i < edges.size(); i++)
    {
        pair<Vertex *, Vertex *> e = edges[i]->getVertexs();
        if ((e.first->getX() == x1 && e.first->getY() == y1 && e.second->getX() == x2 && e.second->getY() == y2) ||
            (e.first->getX() == x2 && e.first->getY() == y2 && e.second->getX() == x1 && e.second->getY() == y1))
        {
            if (this->edges[i]->IsRoad())
            {
                cout << "this road place is taken...\n";
                return false;
            }
            else
            {
                if (p->addFristRoad(edges[i]))
                {
                    this->edges[i]->setRoad(p);
                    return true;
                }
                else
                {
                    cout << "this is your first road you must put it near sattelment";
                    return false;
                }
            }
        }
    }
    cout << "could not find road...\n";
    return false;
}

bool Board::placeSattelment(Player *p, size_t x, size_t y)
{
    if (x > 10)
    {
        return false;
    }
    if (y > 5)
    {
        return false;
    }
    for (size_t i = 0; i < 6; i++)
    {
        for (size_t j = 0; j < 11; j++)
        {
            if (vertexes[i][j] != nullptr)
            {
                if (vertexes[i][j]->getX() == x && vertexes[i][j]->getY() == y)
                {
                    if ((((x % 2 == 0 && y % 2 == 0) || (x % 2 == 1 && y % 2 == 1))&&
                        (i+1<6 && vertexes[i + 1][j] != nullptr && vertexes[i + 1][j]->getOwner() != nullptr)) ||
                        (((x % 2 == 1 && y % 2 == 0) || (x % 2 == 0 && y % 2 == 1)) &&
                        (i != 0 && vertexes[i - 1][j] != nullptr && vertexes[i - 1][j]->getOwner() != nullptr)) ||
                        (j+1<11 && vertexes[i][j + 1] != nullptr && vertexes[i][j + 1]->getOwner() != nullptr) ||
                        (j != 0 && vertexes[i][j - 1] != nullptr && vertexes[i][j - 1]->getOwner() != nullptr))
                    {
                        cout << "cant place sattelment here with sattelment near by\n";
                        return false;
                    }
                    else
                    {
                        if (vertexes[i][j]->getOwner() == nullptr)
                        {
                            if (p->addSattelment(vertexes[i][j]))
                            {
                                p->addPoint();
                                vertexes[i][j]->setSattelment(p);
                                return true;
                            }
                            else
                            {
                                cout << "no resource for this sattelment... or not road to this sattelment...\n";
                                return false;
                            }
                        }
                        else
                        {
                            cout << "this place been takeing...\n";
                            return false;
                        }
                    }
                }
            }
        }
    }
    return false;
}

bool Board::placeRoad(Player *p, size_t x1, size_t y1, size_t x2, size_t y2)
{
    if (x1 > 10)
    {
        return false;
    }
    if (y1 > 5)
    {
        return false;
    }
    if (x2 > 10)
    {
        return false;
    }
    if (y2 > 5)
    {
        return false;
    }
    for (size_t i = 0; i < edges.size(); i++)
    {
        pair<Vertex *, Vertex *> e = edges[i]->getVertexs();
        if ((e.first->getX() == x1 && e.first->getY() == y1 && e.second->getX() == x2 && e.second->getY() == y2) ||
            (e.first->getX() == x2 && e.first->getY() == y2 && e.second->getX() == x1 && e.second->getY() == y1))
        {
            if (this->edges[i]->IsRoad())
            {
                cout << "this road place is taken...\n";
                return false;
            }
            else
            {
                if (p->addRoad(this->edges[i]))
                {
                    this->edges[i]->setRoad(p);
                    return true;
                }
                else
                {
                    cout << "road you must put it near sattelment or another one of your roads\n";
                    return false;
                }
            }
        }
    }
    cout << "could not find road...\n";
    return false;
}

bool Board::placeCity(Player *p, size_t x, size_t y)
{
    if (x > 10)
    {
        return false;
    }
    if (y > 5)
    {
        return false;
    }
    for (size_t i = 0; i < 6; i++)
    {
        for (size_t j = 0; j < 11; j++)
        {
            if (vertexes[i][j] != nullptr)
            {
                if (vertexes[i][j]->getX() == x && vertexes[i][j]->getY() == y)
                {
                    if (vertexes[i][j]->getOwner() != nullptr && !vertexes[i][j]->IsCity() && vertexes[i][j]->getOwner() == p)
                    {
                        if (p->checkResourceTocity())
                        {
                            p->addPoint();
                            vertexes[i][j]->SetCity();
                            return true;
                        }
                        else
                        {
                            cout << "no resource for this sattelment...\n";
                            return false;
                        }
                    }
                    else
                    {
                        cout << "this place must be your sattelment frist\n";
                        return false;
                    }
                }
            }
        }
    }
    return false;
}

bool Board::buyCard(Player *p)
{
    if (Board::cards.size() > 0)
    {
        Cards c = Board::cards[0];
        if (p->buyCard(c))
        {
            Board::cards.erase(Board::cards.begin() + 0);
            return true;
        }
        else
        {
            cout << "no resource to buy...\n";
            return false;
        }
    }
    else
    {
        cout << "there are no more cards to buy...\n";
    }
    return false;
}

void Board::handleRollDice(int roll)
{
    for (size_t i = 0; i < this->tiles.size(); i++)
    {
        if (this->tiles[i]->getNumberToken() == roll)
        {
            for (size_t j = 0; j < this->tiles[i]->getVertex().size(); j++)
            {
                if (this->tiles[i]->getVertex()[j] != nullptr && this->tiles[i]->getVertex()[j]->getOwner() != nullptr && !this->tiles[i]->hasRobber())
                {
                    int max = 1;
                    if (this->tiles[i]->getVertex()[j]->IsCity())
                    {
                        max = +1;
                    }
                    for (int t = 0; t < max; t++)
                    {
                        this->tiles[i]->getVertex()[j]->getOwner()->addResource(this->tiles[i]->getResourceType());
                    }
                }
            }
        }
    }
}

void Board::handelRobber(Player *p)
{
    cout << "TILE IN MAP:" << endl;
    cout << "   |1|2|3|    " << endl;
    cout << "  |4|5|6|7|   " << endl;
    cout << "|8 |9|10|11|12|" << endl;
    cout << " |13|14|15|16| " << endl;
    cout << "  |17|18|19| " << endl;

    bool choos = false;
    while (!choos)
    {
        size_t ans;
        cout << "\nplease enter number of tile for the robber: ";
        cin >> ans;

        if (ans > 0 && ans < 20)
        {
            choos = true;
            for (size_t i = 0; i < this->tiles.size(); i++)
            {
                if (i == ans)
                {
                    this->tiles[i]->setRobberToTrue();
                    Player *p1 = nullptr;
                    Player *p2 = nullptr;
                    for (size_t j = 0; j < this->tiles[i]->getVertex().size(); j++)
                    {
                        if (this->tiles[i]->getVertex()[j]->getOwner() != nullptr && this->tiles[i]->getVertex()[j]->getOwner() != p)
                        {
                            if (p1 == nullptr)
                            {
                                p1 = this->tiles[i]->getVertex()[j]->getOwner();
                            }
                            else
                            {
                                p2 = this->tiles[i]->getVertex()[j]->getOwner();
                            }
                        }
                    }
                    if (!p1 && !p2)
                    {
                        cout << "there are no players on this tile\n";
                    }
                    else
                    {
                        if (p1 && p2)
                        {
                            cout << "you can choos to steel resource from " << p1->getName() << " or from " << p2->getName() << "\n";
                            bool choose = false;
                            while (!choose)
                            {
                                int an;
                                cout << "enter 0 to steel from " << p1->getName() << " enter 1 to steel from " << p2->getName() << endl;
                                cin >> an;
                                if (an == 1 || an == 0)
                                {
                                    choose = true;
                                }
                                else
                                {
                                    cout << "problem input try agian\n";
                                }
                                if (an == 1)
                                {
                                    this->steel(p, p2);
                                }
                                if (an == 0)
                                {
                                    this->steel(p, p1);
                                }
                            }
                        }
                        else
                        {
                            if (p1)
                            {
                                this->steel(p, p1);
                            }
                            if (p2)
                            {
                                this->steel(p, p2);
                            }
                        }
                    }
                }
                else
                {
                    this->tiles[i]->setRobberToFalse();
                }
            }
        }
    }
}

void Board::steel(Player *p, Player *s)
{
    shuffle(s->getResource()->begin(), s->getResource()->end(), random_device());
    TileType t = s->getResource()->at(0);
    s->getResource()->erase(s->getResource()->begin() + 0);
    p->addResource(t);
}

void Board::printBoard()
{
    string middle = "      ";
    size_t tileIndex = 0;
    cout << "\n**************************************************************\n";
    cout << "**********************     MAP:  *****************************";
    cout << "\n**************************************************************\n";
    cout << "y\\x 0  1   2  3   4   5   6   7   8   9  10\n";
    cout << "\n0             ";
    for (size_t i = 0; i < this->vertexes[0].size(); i++)
    {
        if (i % 2 == 1 && this->vertexes[0][i] != nullptr)
        {
            this->ColorVertexByPlayer(vertexes[0][i]->getOwner());
            cout << vertexes[0][i]->printV() << "      ";
            cout << RESET;
        }
    }
    cout << "\n            ";
    // 1
    for (size_t i = 0; i < 6; i++)
    {
        ColorEdgeByPlayer(this->edges[i]->getOwner(), this->edges[i]);
        if (i % 2 == 0)
        {
            cout << " ";
        }
        else
        {
            cout << "   ";
        }
    }
    cout << "\n           ";
    // 2
    for (size_t i = 0; i < 6; i++)
    {
        ColorEdgeByPlayer(this->edges[i]->getOwner(), this->edges[i]);
        if (i % 2 == 0)
        {
            cout << "   ";
        }
        else
        {
            cout << " ";
        }
    }
    // 3.1
    cout << "\n1         ";
    for (size_t i = 0; i < vertexes[0].size(); i++)
    {
        if (i % 2 == 0 && this->vertexes[0][i] != nullptr)
        {
            this->ColorVertexByPlayer(vertexes[0][i]->getOwner());
            cout << vertexes[0][i]->printV() << "      ";
            cout << RESET;
        }
    }
    cout << "\n          ";
    ColorEdgeByPlayer(this->edges[6]->getOwner(), this->edges[6]);
    int t = tileIndex;
    for (size_t i = 7; i < 10; i++)
    {
        cout << YELLOW;
        cout << this->middleStringReplac(middle, this->tiles[t]->tileToString());
        cout << RESET;
        ColorEdgeByPlayer(this->edges[i]->getOwner(), this->edges[i]);
        t++;
    }
    // 3.2
    middle = "      ";
    cout << "\n          ";
    ColorEdgeByPlayer(this->edges[6]->getOwner(), this->edges[6]);
    for (size_t i = 7; i < 10; i++)
    {
        cout << YELLOW;
        middle = middleIntReplace(middle, this->tiles[tileIndex]->getNumberToken());
        if (this->tiles[tileIndex]->hasRobber())
        {
            cout << this->middlePirate(middle);
        }
        else
        {
            cout << middle;
        }
        cout << RESET;
        middle = "      ";
        ColorEdgeByPlayer(this->edges[i]->getOwner(), this->edges[i]);
        tileIndex++;
    }
    cout << "\n2          ";
    for (size_t i = 0; i < this->vertexes[1].size(); i++)
    {
        if (i % 2 == 0 && this->vertexes[1][i] != nullptr)
        {
            this->ColorVertexByPlayer(vertexes[1][i]->getOwner());
            cout << vertexes[1][i]->printV() << "      ";
            cout << RESET;
        }
    }
    cout << "\n         ";
    // 4
    for (size_t i = 10; i < 18; i++)
    {
        ColorEdgeByPlayer(this->edges[i]->getOwner(), this->edges[i]);
        if (i % 2 == 1)
        {
            cout << "    ";
        }
    }
    cout << "\n        ";
    // 5
    for (size_t i = 10; i < 18; i++)
    {
        ColorEdgeByPlayer(this->edges[i]->getOwner(), this->edges[i]);
        cout << "  ";
    }
    cout << "\n3      ";
    for (size_t i = 0; i < this->vertexes[1].size(); i++)
    {
        if (i % 2 == 1 && this->vertexes[1][i] != nullptr)
        {
            this->ColorVertexByPlayer(vertexes[1][i]->getOwner());
            cout << vertexes[1][i]->printV() << "      ";
            cout << RESET;
        }
    }
    cout << "\n      ";
    // 6.1
    t = tileIndex;
    ColorEdgeByPlayer(this->edges[18]->getOwner(), this->edges[18]);
    for (size_t i = 19; i < 23; i++)
    {
        cout << YELLOW;
        cout << this->middleStringReplac(middle, this->tiles[t]->tileToString());
        cout << RESET;
        ColorEdgeByPlayer(this->edges[i]->getOwner(), this->edges[i]);
        t++;
    }
    middle = "      ";
    cout << "\n      ";
    // 6.2
    ColorEdgeByPlayer(this->edges[18]->getOwner(), this->edges[18]);
    for (size_t i = 19; i < 23; i++)
    {
        cout << YELLOW;
        middle = middleIntReplace(middle, this->tiles[tileIndex]->getNumberToken());
        if (this->tiles[tileIndex]->hasRobber())
        {
            cout << this->middlePirate(middle);
        }
        else
        {
            cout << middle;
        }
        cout << RESET;
        middle = "      ";
        ColorEdgeByPlayer(this->edges[i]->getOwner(), this->edges[i]);
        tileIndex++;
    }
    cout << "\n4     ";
    for (size_t i = 0; i < vertexes[2].size(); i++)
    {
        if (i % 2 == 1 && this->vertexes[2][i] != nullptr)
        {
            this->ColorVertexByPlayer(vertexes[2][i]->getOwner());
            cout << vertexes[2][i]->printV() << "      ";
            cout << RESET;
        }
    }
    cout << "\n     ";
    // 7
    for (size_t i = 23; i < 33; i++)
    {
        ColorEdgeByPlayer(this->edges[i]->getOwner(), this->edges[i]);
        if (i % 2 == 0)
        {
            cout << "    ";
        }
    }
    cout << "\n    ";
    // 8
    for (size_t i = 23; i < 33; i++)
    {
        ColorEdgeByPlayer(this->edges[i]->getOwner(), this->edges[i]);
        cout << "  ";
    }
    cout << "\n5  ";
    for (size_t i = 0; i < this->vertexes[2].size(); i++)
    {
        if (i % 2 == 0 && this->vertexes[2][i] != nullptr)
        {
            this->ColorVertexByPlayer(vertexes[2][i]->getOwner());
            cout << vertexes[2][i]->printV() << "      ";
            cout << RESET;
        }
    }
    cout << "\n   ";
    // 9.1
    t = tileIndex;
    middle = "     ";
    ColorEdgeByPlayer(this->edges[33]->getOwner(), this->edges[33]);
    for (size_t i = 34; i < 39; i++)
    {
        cout << YELLOW;
        cout << this->middleStringReplac(middle, this->tiles[t]->tileToString());
        cout << RESET;
        ColorEdgeByPlayer(this->edges[i]->getOwner(), this->edges[i]);
        t++;
        middle = "      ";
    }
    middle = "     ";
    cout << "\n   ";
    // 9.2
    ColorEdgeByPlayer(this->edges[33]->getOwner(), this->edges[33]);
    for (size_t i = 34; i < 39; i++)
    {
        cout << YELLOW;
        middle = middleIntReplace(middle, this->tiles[tileIndex]->getNumberToken());
        if (this->tiles[tileIndex]->hasRobber())
        {
            cout << this->middlePirate(middle);
        }
        else
        {
            cout << middle;
        }
        cout << RESET;
        middle = "      ";
        ColorEdgeByPlayer(this->edges[i]->getOwner(), this->edges[i]);
        tileIndex++;
    }
    cout << "\n6  ";
    for (size_t i = 0; i < this->vertexes[3].size(); i++)
    {
        if (i % 2 == 0 && this->vertexes[3][i] != nullptr)
        {
            this->ColorVertexByPlayer(vertexes[3][i]->getOwner());
            cout << vertexes[3][i]->printV() << "      ";
            cout << RESET;
        }
    }
    cout << "\n    ";
    // 10
    for (size_t i = 39; i < 49; i++)
    {
        ColorEdgeByPlayer(this->edges[i]->getOwner(), this->edges[i]);
        cout << "  ";
    }
    cout << "\n     ";
    // 11
    for (size_t i = 39; i < 49; i++)
    {
        ColorEdgeByPlayer(this->edges[i]->getOwner(), this->edges[i]);
        if (i % 2 == 0)
        {
            cout << "    ";
        }
    }
    cout << "\n7     ";
    for (size_t i = 0; i < this->vertexes[3].size(); i++)
    {
        if (i % 2 == 1 && this->vertexes[3][i] != nullptr)
        {
            this->ColorVertexByPlayer(vertexes[2][i]->getOwner());
            cout << vertexes[3][i]->printV() << "      ";
            cout << RESET;
        }
    }
    cout << "\n      ";
    // 12.1
    t = tileIndex;
    ColorEdgeByPlayer(this->edges[49]->getOwner(), this->edges[49]);
    for (size_t i = 50; i < 54; i++)
    {
        cout << YELLOW;
        cout << this->middleStringReplac(middle, this->tiles[t]->tileToString());
        cout << RESET;
        ColorEdgeByPlayer(this->edges[i]->getOwner(), this->edges[i]);
        t++;
    }
    middle = "      ";
    cout << "\n      ";
    // 12.2
    ColorEdgeByPlayer(this->edges[49]->getOwner(), this->edges[49]);
    for (size_t i = 50; i < 54; i++)
    {
        cout << YELLOW;
        middle = middleIntReplace(middle, this->tiles[tileIndex]->getNumberToken());
        if (this->tiles[tileIndex]->hasRobber())
        {
            cout << this->middlePirate(middle);
        }
        else
        {
            cout << middle;
        }
        cout << RESET;
        middle = "      ";
        ColorEdgeByPlayer(this->edges[i]->getOwner(), this->edges[i]);
        tileIndex++;
    }
    cout << "\n8      ";
    for (size_t i = 0; i < this->vertexes[4].size(); i++)
    {
        if (i % 2 == 1 && this->vertexes[4][i] != nullptr)
        {
            this->ColorVertexByPlayer(vertexes[4][i]->getOwner());
            cout << vertexes[4][i]->printV() << "      ";
            cout << RESET;
        }
    }
    // 13
    cout << "\n        ";
    for (size_t i = 54; i < 62; i++)
    {
        ColorEdgeByPlayer(this->edges[i]->getOwner(), this->edges[i]);
        cout << "  ";
    }
    // 14
    cout << "\n         ";
    for (size_t i = 54; i < 62; i++)
    {
        ColorEdgeByPlayer(this->edges[i]->getOwner(), this->edges[i]);
        if (i % 2 == 1)
        {
            cout << "    ";
        }
    }
    cout << "\n9         ";
    for (size_t i = 0; i < this->vertexes[4].size(); i++)
    {
        if (i % 2 == 0 && this->vertexes[4][i] != nullptr)
        {
            this->ColorVertexByPlayer(vertexes[4][i]->getOwner());
            cout << vertexes[4][i]->printV() << "      ";
            cout << RESET;
        }
    }
    cout << "\n          ";
    // 15.1
    t = tileIndex;
    ColorEdgeByPlayer(this->edges[62]->getOwner(), this->edges[62]);
    for (size_t i = 63; i < 66; i++)
    {
        cout << YELLOW;
        cout << this->middleStringReplac(middle, this->tiles[t]->tileToString());
        cout << RESET;
        ColorEdgeByPlayer(this->edges[i]->getOwner(), this->edges[i]);
        t++;
    }
    middle = "      ";
    cout << "\n          ";
    // 15.2
    ColorEdgeByPlayer(this->edges[62]->getOwner(), this->edges[62]);
    for (size_t i = 63; i < 66; i++)
    {
        cout << YELLOW;
        middle = middleIntReplace(middle, this->tiles[tileIndex]->getNumberToken());
        if (this->tiles[tileIndex]->hasRobber())
        {
            cout << this->middlePirate(middle);
        }
        else
        {
            cout << middle;
        }
        cout << RESET;
        middle = "      ";
        ColorEdgeByPlayer(this->edges[i]->getOwner(), this->edges[i]);
        tileIndex++;
    }
    cout << "\n10         ";
    for (size_t i = 0; i < this->vertexes[5].size(); i++)
    {
        if (i % 2 == 0 && this->vertexes[5][i] != nullptr)
        {
            this->ColorVertexByPlayer(vertexes[5][i]->getOwner());
            cout << vertexes[5][i]->printV() << "      ";
            cout << RESET;
        }
    }
    cout << "\n            ";
    // 16
    for (size_t i = 66; i < 72; i++)
    {
        ColorEdgeByPlayer(this->edges[i]->getOwner(), this->edges[i]);
        cout << "  ";
    }
    cout << "\n             ";
    // 17
    for (size_t i = 66; i < 72; i++)
    {
        ColorEdgeByPlayer(this->edges[i]->getOwner(), this->edges[i]);
        if (i % 2 == 1)
        {
            cout << "    ";
        }
    }
    cout << "\n11            ";
    for (size_t i = 0; i < this->vertexes[5].size(); i++)
    {
        if (i % 2 == 1 && this->vertexes[5][i] != nullptr)
        {
            this->ColorVertexByPlayer(vertexes[5][i]->getOwner());
            cout << vertexes[5][i]->printV() << "      ";
            cout << RESET;
        }
    }
    cout << "\n";
}

void Board::ColorVertexByPlayer(Player *p)
{
    if (p != nullptr)
    {
        if (p->getColor().compare("red"))
        {
            cout << RED;
        }
        if (p->getColor().compare("green"))
        {
            cout << GREEN;
        }
        if (p->getColor().compare("blue"))
        {
            cout << BLUE;
        }
    }
    else
    {
        cout << YELLOW;
    }
}

void Board::ColorEdgeByPlayer(Player *p, Edge *e)
{
    if (p != nullptr)
    {
        if (p->getColor().compare("red"))
        {
            cout << RED;
        }
        if (p->getColor().compare("green"))
        {
            cout << GREEN;
        }
        if (p->getColor().compare("blue"))
        {
            cout << BLUE;
        }
    }
    cout << e->getEdge();
    cout << RESET;
}

string Board::middleStringReplac(string middle, string insert)
{
    middle.replace(0, insert.length(), insert);
    return middle;
}

string Board::middleIntReplace(string middle, int num)
{
    if (num != 0)
    {
        int i = 1;
        if (num > 9)
        {
            i = 2;
        }
        middle.replace(1, i, to_string(num));
    }
    return middle;
}

string Board::middlePirate(string middle)
{
    string p = ",☠";
    middle.replace(3, 2, p);
    return middle;
}



// catan.cpp

#include "catan.hpp"

using namespace std;

int Catan::maxRoad = 4;
Player *Catan::maxRoadPlayer = nullptr;

int Catan::maxArmy = 2;
Player *Catan::maxArmyPlayer = nullptr;

Catan::Catan()
{
    cout << "\nEnter name for red player 1: ";
    string name1, name2, name3;
    cin >> name1;
    cout << "\nEnter name for green player 2: ";
    cin >> name2;
    cout << "\nEnter name for blue player 3: ";
    cin >> name3;

    Player *p1 = new Player(name1, "red");
    Player *p2 = new Player(name2, "green");
    Player *p3 = new Player(name3, "blue");

    this->players = {p1, p2, p3};
    shuffle(players.begin(), players.end(), random_device());

    this->board = Board();

    Catan::maxRoad = 4;
    Catan::maxRoadPlayer = nullptr;

    Catan::maxArmy = 2;
    Catan::maxArmyPlayer = nullptr;
}

Catan::~Catan()
{
    for (auto player : players)
    {
        delete player;
    }
}

void Catan::startGame()
{
    cout << "first step each player will choose and place two sattelment and two roads\n";
    for (size_t t = 0; t < 2; t++)
    {
        for (size_t i = 0; i < this->players.size(); i++)
        {
            this->board.printBoard();
            bool choose1 = false;
            bool choose2 = false;
            size_t x1;
            size_t y1;
            size_t x2;
            size_t y2;
            while (!choose1)
            {
                cout << "\nplayer: " << this->players[i]->getName() << " enter x for sattelment: ";
                cin >> x1;
                cout << "\nplayer: " << this->players[i]->getName() << " enter y for sattelment: ";
                cin >> y1;
                choose1 = this->board.startPlaceingSattelment(this->players[i], x1, this->UpdateUserYtoMap(y1));
                if (!choose1)
                {
                    cout << "problem with loction for sattelment lets try agian...\n";
                }
            }
            while (!choose2)
            {
                cout << "\nplayer: " << this->players[i]->getName() << " enter x for road end vertex: ";
                cin >> x2;
                cout << "\nplayer: " << this->players[i]->getName() << " enter y for road end vertex: ";
                cin >> y2;
                choose2 = this->board.startPlacingRoad(this->players[i], x1, this->UpdateUserYtoMap(y1), x2, this->UpdateUserYtoMap(y2));
                if (!choose2)
                {
                    cout << "problem placeing road lets try agian...\n";
                }
            }
        }
    }

    cout << "great every one place two sattelment and two road let move to step 2\n";
}

void Catan::turn(Player *p)
{
    int knight = 0;
    int monopoly = 0;
    int roadBuilding = 0;
    int victoryPoint = 0;
    int YearOfPlenty = 0;
    for(size_t i=0; i<p->getCardToUse().size(); i++) {
        Cards c = p->getCardToUse().at(i);
        if(c == Cards::Knight) {knight++;}
        if(c== Cards::monopoly) {monopoly++;}
        if(c == Cards::roadBuilding) {roadBuilding++;}
        if(c == Cards::victoryPoint) {victoryPoint++;}
        if( c == Cards::YearOfPlenty) {YearOfPlenty++;}
    }
    int wheat = 0, wood = 0, brick = 0, sheep = 0, lead = 0;
    for(size_t i=0; i<p->getResource()->size(); i++) {
        if(p->getResource()->at(i)==TileType::BRICK) {brick++;}
        if(p->getResource()->at(i)==TileType::LEAD) {lead++;}
        if(p->getResource()->at(i)==TileType::SHEEP) {sheep++;}
        if(p->getResource()->at(i)==TileType::WHEAT) {wheat++;}
        if(p->getResource()->at(i)==TileType::WOOD) {wood++;}
    }
    board.printBoard();
    cout << "\n       **** it is " << p->getName() << " turn, your poins: " << p->getPoints() << " ****";
    cout << "\n*resource: ||wood-" << to_string(wood) << "||lead-" <<to_string(lead) << "||sheep-" << to_string(sheep) << "||brick-" <<to_string(brick) << "||wheat-"<<to_string(wheat)<<"||";
    cout << "\n*card: ||knight-" << to_string(knight) << "||monopoly-" << to_string(monopoly) << "||roadBuilding-" << to_string(roadBuilding)<< "||victoryPoint-" <<to_string(victoryPoint)<< "||YearOfPlenty-"<<to_string(YearOfPlenty)<<"||"; 
    cout << "\n**************************************************************\n";
    bool card = true;
    while (card)
    {
        string ans;
        cout << "\nwould you like to use card? Enter y for yes and n for no: ";
        cin >> ans;
        if (ans == "n")
        {
            card = false;
        }
        else
        {
            this->useingCard(p);
        }
    }

    int roll = p->rollDice();
    cout << "throwing dice got: " << roll << endl;
    // robber
    if (roll == 7)
    {
        board.handelRobber(p);
    }
    else
    {
        this->board.handleRollDice(roll);
    }
    cout << "it time for player: " << p->getName() << " to play what would you like to do?\n";
    bool endTurn = false;
    while (!endTurn)
    {
        int ans;
        cout << "Enter 0 to end your turn\n";
        cout << "Enter 1 for new sattelment\n";
        cout << "Enter 2 for new road\n";
        cout << "Enter 3 for new city\n";
        cout << "Enter 4 for trade resource\n";
        cout << "Enter 5 for use card\n";
        cout << "Enter 6 for buying card\n";

        cin >> ans;
        if (ans == 0)
        {
            break;
        }
        if (ans == 1)
        {
            bool choose1;
            size_t x1;
            size_t y1;
            cout << "\nplayer: " << p->getName() << "enter x for sattelment: ";
            cin >> x1;
            cout << "\nplayer: " << p->getName() << "enter y for sattelment: ";
            cin >> y1;
            choose1 = this->board.placeSattelment(p, x1, y1);
            if (!choose1)
            {
                cout << "problem with loction for sattelment...\n";
            }
        }
        if (ans == 2)
        {
            bool choose1;
            size_t x1;
            size_t y1;
            size_t x2;
            size_t y2;
            cout << "\nplayer: " << p->getName() << "enter x for road start: ";
            cin >> x1;
            cout << "\nplayer: " << p->getName() << "enter y for road start: ";
            cin >> y1;
            cout << "\nplayer: " << p->getName() << "enter x for roadend: ";
            cin >> x2;
            cout << "\nplayer: " << p->getName() << "enter y for roadend: ";
            cin >> y2;
            choose1 = this->board.placeRoad(p, x1, y1, x2, y2);
            if (!choose1)
            {
                cout << "problem with loction for sattelment...\n";
            }
        }
        if (ans == 3)
        {
            bool choose1;
            size_t x1;
            size_t y1;
            cout << "\nplayer: " << p->getName() << "enter x for city: ";
            cin >> x1;
            cout << "\nplayer: " << p->getName() << "enter y for city: ";
            cin >> y1;
            choose1 = this->board.placeCity(p, x1, y1);
            if (!choose1)
            {
                cout << "problem with loction for city...\n";
            }
        }
        if (ans == 4)
        {
        }
        if (ans == 5)
        {
            this->useingCard(p);
        }
        if (ans == 6)
        {
            this->board.buyCard(p);
        }
    }
    cout << "end turn player: " << p->getName() << endl;

    // card can only be using on the next turn
    p->endturnMoveCards();

    // biggest army remove points check for new and add points
    if (this->maxArmyPlayer != nullptr)
    {
        this->maxArmyPlayer->removePoint();
        this->maxArmyPlayer->removePoint();
    }
    checkBigestArmy();
    if (this->maxArmyPlayer != nullptr)
    {
        this->maxArmyPlayer->addPoint();
        this->maxArmyPlayer->addPoint();
    }

    // longest road remove points check for new and add points
    if (this->maxRoadPlayer != nullptr)
    {
        this->maxRoadPlayer->removePoint();
        this->maxRoadPlayer->removePoint();
    }
    checkLongestRoad();
    if (this->maxRoadPlayer != nullptr)
    {
        this->maxRoadPlayer->addPoint();
        this->maxRoadPlayer->addPoint();
    }
}

Player *Catan::checkWin()
{
    for (size_t i = 0; i < this->players.size(); i++)
    {
        if (this->players[i]->getPoints() > 9)
        {
            return this->players[i];
        }
    }
    return nullptr;
}

void Catan::useingCard(Player *p)
{
    int i = p->useCard();
    if (i < 0)
    {
        cout << "it seem we have problem choosing card\n";
    }
    if (i == 0)
    {
        cout << "card has been used\n";
    }
    if (i == 1)
    {
        board.handelRobber(p);
    }
    if (i == 2)
    {
        TileType t;
        bool temp = false;
        while (!temp)
        {
            int ans1;

            cout << "please choose resource:\n";
            cout << "enter 1 for wood\n";
            cout << "enter 2 for brick\n";
            cout << "enter 3 for sheep\n";
            cout << "enter 4 for wheat\n";
            cout << "enter 5 for lead\n";
            cout << "\nenter your anser here: ";
            cin >> ans1;

            if (ans1 < 6 && ans1 > 0)
            {
                temp = true;
                if (ans1 == 1)
                {
                    t = TileType::WOOD;
                }
                if (ans1 == 2)
                {
                    t = TileType::BRICK;
                }
                if (ans1 == 3)
                {
                    t = TileType::SHEEP;
                }
                if (ans1 == 4)
                {
                    t = TileType::WHEAT;
                }
                if (ans1 == 5)
                {
                    t = TileType::LEAD;
                }
            }
            int sum = 0;
            for (size_t indexp = 0; indexp < this->players.size(); indexp++)
            {
                for (size_t indexr = 0; indexr < this->players[indexp]->getResource()->size(); indexr++)
                {
                    if (this->players[indexp]->getResource()->at(indexr) == t)
                    {
                        sum++;
                        this->players[indexp]->getResource()->erase(this->players[indexp]->getResource()->begin() + indexr);
                    }
                }
            }
            for (int l = 0; l < sum; l++)
            {
                p->addResource(t);
            }
        }
    }
    if (i == 3)
    {
        for (int l = 0; l < 2; l++)
        {
            bool choose1 = false;
            while (!choose1)
            {
                size_t x1;
                size_t y1;
                size_t x2;
                size_t y2;
                cout << "\nplayer: " << p->getName() << "enter x for road start: ";
                cin >> x1;
                cout << "\nplayer: " << p->getName() << "enter y for road start: ";
                cin >> y1;
                cout << "\nplayer: " << p->getName() << "enter x for roadend: ";
                cin >> x2;
                cout << "\nplayer: " << p->getName() << "enter y for roadend: ";
                cin >> y2;
                choose1 = this->board.placeRoad(p, x1, y1, x2, y2);
                if (!choose1)
                {
                    cout << "problem with loction for sattelment...\n";
                }
            }
        }
    }
}

void Catan::checkLongestRoad()
{
    for (size_t i = 0; i < this->players.size(); i++)
    {
        if (players[i]->getNumberOfRoads() > this->maxRoad)
        {
            this->maxRoad = players[i]->getNumberOfRoads();
            this->maxRoadPlayer = players[i];
        }
    }
}

void Catan::checkBigestArmy()
{
    for (size_t i = 0; i < this->players.size(); i++)
    {
        if (players[i]->getArmy() > this->maxArmy)
        {
            this->maxArmy = players[i]->getArmy();
            this->maxArmyPlayer = players[i];
        }
    }
}

size_t Catan::UpdateUserYtoMap(size_t y) {
    size_t ans = 0;
    if(y%2==0) {ans = y/2;}
    else {ans = (y-1)/2;}
    return ans;
}

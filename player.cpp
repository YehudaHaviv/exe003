
// player.cpp

#include "player.hpp"


// constractor 
Player::Player(string name, string color) {
    if(name=="") {
        throw runtime_error("must enter name");
    }
    else {this->name = name;}

    this->color = color;

    this->Resource.resize(0);
    this->CardsToUse.resize(0);
    this->CardToNextTurn.resize(0);
    this->places.resize(0);

    this->points = 0;
    this->army = 0;
    this->numberOfraod = 0;    
}
        
string Player::getColor() {
    return this->color;
}

// return name of player
string Player::getName() {return this->name;}
        

// return resource of player
vector<TileType>* Player::getResource() {return &(this->Resource);}

// return players point
int Player::getPoints() {return this->points;}
 
//return size of player army
int Player::getArmy() {return this->army;}

// return size of the long road player
int Player::getNumberOfRoads() {return this->numberOfraod;}

vector<Cards> Player::getCardToUse() {
    return this->CardsToUse;
}

// add and remove points
void Player::addPoint() {this->points++;}
void Player::removePoint() {this->points--;}


// return sum of rolling two dice
int Player::rollDice() {
    // Create a random device to seed the random number generator
    std::random_device rd;
    // Use the Mersenne Twister engine to generate random numbers
    std::mt19937 gen(rd());
    // Define the distribution to produce numbers in the range [1, 6]
    std::uniform_int_distribution<> dis(1, 6);
    // Simulate rolling two dice
    int die1 = dis(gen);
    int die2 = dis(gen);
    // Return the sum of the two dice
    return die1 + die2;
}

// add to player resource
bool Player::addResource(TileType Resource) {
    this->Resource.resize(this->Resource.size()+1);
    this->Resource.push_back(Resource);
    return true;
}

// remove from player resource
bool Player::removeResource(TileType resource) {
    for(size_t i=0; i<this->Resource.size(); i++) {
        if(this->Resource[i]==resource) {
            this->Resource.erase(this->Resource.begin()+i);
            return true;
        }
    }
    return false;
}

// checking and return true if player have resource to biuld sattelment and removing them and return false otherwise
bool Player::checkResourceToSattelment() {
    vector<TileType> price = {TileType::WOOD, TileType::WHEAT, TileType::BRICK, TileType::SHEEP};
    size_t one=1000, two=1000, three=1000, four=1000;
    for(size_t i=0; i<this->Resource.size(); i++) {
        for(size_t j=0; j<price.size(); j++) {
            if(this->Resource[i]==price[j]) {
                price.erase(price.begin()+j);
                if(one==1000) {one=i;}
                else{ if(two==1000) {two=i;}
                else{ if(three==1000) {three=i;}
                else{ four = i;}}}
            }
            if(price.size()==0) {
                this->Resource.erase(this->Resource.begin()+one);
                this->Resource.erase(this->Resource.begin()+two);
                this->Resource.erase(this->Resource.begin()+three);
                this->Resource.erase(this->Resource.begin()+four);
                return true;
            }
        }
    }
    return false;
}

// checking and return true if player have resource to biuld road and removing them and return false otherwise
bool Player::checkResourceToRoad() {
    vector<TileType> price = {TileType::BRICK, TileType::WOOD};
    size_t one=1000, two=1000;
    for(size_t i=0; i<this->Resource.size(); i++) {
        for(size_t j=0; j<price.size(); j++) {
            if(this->Resource[i]==price[j]) {
                price.erase(price.begin()+j);
                if(one==1000) {one=i;}
                else {two=i;}
            }
            if(price.size()==0) {
                this->Resource.erase(this->Resource.begin()+one);
                this->Resource.erase(this->Resource.begin()+two);
                return true;
            }
        }
    }
    return false;
}
// checking and return true if player have resource to buy card and removing them and return false otherwise
bool Player::checkResourceToCard() {
    vector<TileType> price = {TileType::SHEEP, TileType::LEAD, TileType::WHEAT};
    size_t one=1000, two=1000, three=1000;
    for(size_t i=0; i<this->Resource.size(); i++) {
        for(size_t j=0; j<price.size(); j++) {
            if(this->Resource[i]==price[j]) {
                price.erase(price.begin()+j);
                if(one==1000) {one=i;}
                else {if(two==1000) {two=i;}
                      else{three=i;}  
                }
            }
            if(price.size()==0) {
                this->Resource.erase(this->Resource.begin()+one);
                this->Resource.erase(this->Resource.begin()+two);
                this->Resource.erase(this->Resource.begin()+three);
                return true;
            }
        }
    }
    return false;
}

// checking and return true if player have resource to biuld city and removing them and return false otherwise
bool Player::checkResourceTocity() {
    vector<TileType> price = {TileType::LEAD, TileType::LEAD, TileType::LEAD, TileType::LEAD, TileType::LEAD};
    size_t one=1000, two=1000, three=1000, four=1000, five=1000;
    for(size_t i=0; i<this->Resource.size(); i++) {
        for(size_t j=0; j<price.size(); j++) {
            if(this->Resource[i]==price[j]) {
                price.erase(price.begin()+j);
                if(one==1000) {one=i;}
                else{ if(two==1000) {two=i;}
                else{ if(three==1000) {three=i;}
                else{ if(four==1000) {four = i;}
                else {five=i;}
                }}}
            }
            if(price.size()==0) {
                this->Resource.erase(this->Resource.begin()+one);
                this->Resource.erase(this->Resource.begin()+two);
                this->Resource.erase(this->Resource.begin()+three);
                this->Resource.erase(this->Resource.begin()+four);
                this->Resource.erase(this->Resource.begin()+five);
                return true;
            }
        }
    }
    return false;
} 
        
// check player point > 9 
bool Player::checkWin() {
    return this->points>9;
}

// add first sattelment 
void Player::addFirstSattelment(Vertex* v) {
    this->places.push_back(v);
}

bool Player::addFristRoad(Edge* e) {
    for(size_t i=0; i<this->places.size(); i++) {
        if(this->places[i]==e->getVertexs().first||this->places[i]==e->getVertexs().second) {
            this->road.push_back(e);
            return true;
        }
    }
    return false;
}

// check if can biuld sattelment there
bool Player::addSattelment(Vertex* v) {
    for(size_t i=0; i<this->road.size(); i++) {
        if(this->road[i]->getVertexs().first==v||this->road[i]->getVertexs().second==v) {
            if(this->checkResourceToSattelment()) {
                this->places.push_back(v);
                return true;
            }
            else {
                cout << "you dint have the resource\n";
                return false;
            }
        }
    }
    return false;
}

// check if can biuld road there
bool Player::addRoad(Edge* e) {
    for(size_t i=0; i<this->road.size(); i++) {
        if(this->road[i]->getVertexs().first==e->getVertexs().first||this->road[i]->getVertexs().second==e->getVertexs().second||
            this->road[i]->getVertexs().second==e->getVertexs().first||this->road[i]->getVertexs().second==e->getVertexs().second) {
            if(this->checkResourceToRoad()) {
                this->road.push_back(e);
                this->addtoroad();
                return true;
            }
            else {
                cout << "you dont have the resource\n";
                return false;
            }
        }
    }
    for(size_t i=0; i<this->places.size(); i++) {
        if(this->places[i]==e->getVertexs().first||this->places[i]==e->getVertexs().second) {
            if(this->checkResourceToRoad()) {
                this->road.push_back(e);
                return true;
            }
            else {
                cout << "you dont have the resource\n";
                return false;
            }
        }
    }
    return false;
}

// add by one to road or army
void Player::addtoroad() {this->numberOfraod++;}

void Player::addtoarmy() {this->army++;}  


// buy and use card
bool Player::buyCard(Cards c) {
    if(checkResourceToCard()) {
        this->CardToNextTurn.push_back(c);
        return true;
    }
    return false;
}
        
int Player::useCard() {
    int knight = 0;
    int monopoly = 0;
    int roadBuilding = 0;
    int victoryPoint = 0;
    int YearOfPlenty = 0;
    for(size_t i=0; i<this->CardsToUse.size(); i++) {
        Cards c = this->CardsToUse[i];
        if(c == Cards::Knight) {knight++;}
        if(c== Cards::monopoly) {monopoly++;}
        if(c == Cards::roadBuilding) {roadBuilding++;}
        if(c == Cards::victoryPoint) {victoryPoint++;}
        if( c == Cards::YearOfPlenty) {YearOfPlenty++;}
    }

    int ans;

    cout << "this are the cards you have and can use:\n";
    cout << knight << " knight - enter: 1 to use\n";
    cout << monopoly << " monopoly - enter: 2 to use\n";
    cout << roadBuilding << " x2 road building - enter: 3 to use\n";
    cout << victoryPoint << " victory point - enter: 4 to use\n";
    cout << YearOfPlenty << " year of plenty - enter: 5 to use\n";
    cout << "\nplease enter your anser here: ";

    cin >> ans;

    switch (ans)
    {
    case 1:
        if(knight<1) {
            cout << "you choose knight but dont have any...\n";
            break;
        }
        else {
            for(size_t i=0; i<this->CardsToUse.size(); i++) {
                if(this->CardsToUse[i] == Cards::Knight) {
                    this->army++;
                    this->CardsToUse.erase(this->CardsToUse.begin()+i);
                    return 1; 
                }
            }
        }
        break;
    case 2:
        if(monopoly<1) {
            cout << "you choose monapoly but dont have any...\n";
            break;
        }
        else {
            for(size_t i=0; i<this->CardsToUse.size(); i++) {
                if(this->CardsToUse[i] == Cards::monopoly) {
                    this->CardsToUse.erase(this->CardsToUse.begin()+i);
                    return 2; 
                }
            }
        }
        break;
    case 3:
        if(roadBuilding<1) {
            cout << "you choose road building but dont have any...\n";
            break;
        }
        else {
            for(size_t i=0; i<this->CardsToUse.size(); i++) {
                if(this->CardsToUse[i] == Cards::roadBuilding) {
                    this->CardsToUse.erase(this->CardsToUse.begin()+i);
                    return 3; 
                }
            }
        }
        break;
    case 5:
        if(YearOfPlenty<1) {
            cout << "you choose year of plenty but dont have any...\n";
            break;
        }
        else {
            for(size_t i=0; i<this->CardsToUse.size(); i++) {
                if(this->CardsToUse[i] == Cards::YearOfPlenty) {
                    this->CardsToUse.erase(this->CardsToUse.begin()+i);

                    bool temp = false;
                    TileType t;

                    while(!temp) {
                        int ans1;

                        cout << "please choose resource:\n";
                        cout << "enter 1 for wood\n";
                        cout << "enter 2 for brick\n";
                        cout << "enter 3 for sheep\n";
                        cout << "enter 4 for wheat\n";
                        cout << "enter 5 for lead\n";
                        cout << "\nenter your anser here: ";
                        cin >> ans1;

                    if(ans1<6&&ans1>0) {
                        temp = true;
                        if(ans1==1) {t=TileType::WOOD;}
                        if(ans1==2) {t=TileType::BRICK;}
                        if(ans1==3) {t=TileType::SHEEP;}
                        if(ans1==4) {t=TileType::WHEAT;}
                        if(ans1==5) {t=TileType::LEAD;}
                    }
                    }
                    for(int i=0; i<2; i++) {
                        this->addResource(t);
                    }
                    return 0;
                }
            }
        }
        break;
    case 4:
        if(victoryPoint<1) {
            cout << "you choose victory point but dont have any...\n";
            break;
        }
        else {
            for(size_t i=0; i<this->CardsToUse.size(); i++) {
                if(this->CardsToUse[i] == Cards::YearOfPlenty) {
                    this->CardsToUse.erase(this->CardsToUse.begin()+i);
                    this->points++;
                    return 0;
                }
            }    
        }
        break;
    default:
        cout << "some problem with your choise \n";
        break;
    }

    return -1;
}

void Player::endturnMoveCards() {
    for(size_t i=0; i < this->CardToNextTurn.size(); i++) {
        this->CardsToUse.push_back(this->CardToNextTurn[i]);
        this->CardToNextTurn.erase(this->CardToNextTurn.begin()+i);
    }
}

          
          
        
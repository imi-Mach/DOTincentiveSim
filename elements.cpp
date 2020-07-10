#include "elements.hpp"

Cell::Cell(int travelCost) {
    int cost = travelCost;
}

void Cell::addEntity(Entity* enteringEntity) {
    
    int size;
    int i;

    /* empty vector case */
    if(entityVector.empty()) {
        entityVector.push_back(enteringEntity);
        return;
    }

    size = entityVector.size();

    /* scan through vector for NULL pointers */
    for(i = 0; i < size; i++) {
        if(entityVector[i] == nullptr) {
            entityVector[i] = enteringEntity;
            return;
        }
    }

    /* vector is full, add another container */
    entityVector.push_back(enteringEntity);

}

void Cell::delEntity(Entity* leavingEntity) {
    int size = entityVector.size();
    for(int i = 0; i < size; i++) {
        if(entityVector[i] == leavingEntity) {
            entityVector[i] = nullptr;
            return;
        }
    }
}

Cell::~Cell() {

}

void Entity::setCoord(const char component, int posVal) {
    switch(component) {
        case 'x':
            x = posVal;
            return;
            break;

        case 'y':
            y = posVal;
            return;
            break;
        
        default:

    }
    bail(2, "Incorrect use of setCoord function");
    cerr << "FATAL error: setCoord failed to return coord or error!" << endl;
    return;
}

int Entity::getCoord(const char component) {
    switch(component) {
        case 'x':
            return x;
            break;

        case 'y':
            return y;
            break;
        
        default:

    }
    bail(2, "Incorrect use of getCoord function");
    cerr << "FATAL error: getCoord failed to return coord or error!" << endl;
    return -2;
}

User::User() {
    SID       = 0;
    x         = -1;
    y         = -1;
    opTime    = 0;
    opCost    = 0;
    distance  = 0;
    accReward = 0.0;
}

void User::set(int x, int y) {
    
}

int User::selectSID(SensingTask *sensingTaskList) {
    
}

User::~User() {

}

SensingTask::SensingTask(int indexSID, float incentive) {
    SID         = indexSID;
    x           = -1;
    y           = -1;
    status      = false;
    reward      = incentive;
    participant = NULL;
}

void SensingTask::set(int x, int y) {
    
}

SensingTask::~SensingTask() {

}

Enviroment::Enviroment(int size) { 

    int cost = 1; /* cost for traveling into a cell */

    for(int i = 0; i < size; i++)  {
        vector<Cell> v;
        for(int i = 0; i < size; i++) {
                v.push_back(Cell(cost));
        }
        grid.push_back(v);
    }
    
}

void Enviroment::set(int numUsers, int numIncent) {

}

void Enviroment::placeEntity(Entity* newEntity) {

}

Cell* Enviroment::getCell(int x, int y) {

}

Enviroment::~Enviroment() {

}

Game::Game(int numIncent, int numUser, int size, float predictedBudget) {
    /*
    * Game constructor:
    *   - Responsible for initializing all variables
    *       - local variables intialized
    *       - enviroment constructed and pointed to
    *       - set of users constructed and pointed to
    *       - set of sensing tasks constructed and pointed to
    */

    state = CONSTRUCTION;
    totalTime = 0;
    totalIncentives = numIncent;
    totalUsers = numUser;
    boardSize = size;
    preBudget = predictedBudget;

    board = new Enviroment(boardSize);

    for(int i = 0; i < numUser; i++) {
        userList.push_back(User());
    }

    for(int i = 0; i < numIncent; i++) {
        taskList.push_back(SensingTask(i+1, preBudget/((float) numIncent)));
    }

}

void Game::set() {
    /* 
    * set outline:
    *   - place all users and incentives in some cells
    * 
    */

    random_shuffle
    

}

void Game::play() {
    /*
    * Outline:
    *   - at start, all users are randomly selected to select sensing task (shuffle)
    *   - each turn updates board stats
    *       -players can move on to the same space
    *   - game ends if there are only unavaliable users
    */

   

}

void Game::save() {

}

void Game::reset() {

}

void Game::movUser(User* movingUser, Cell* oldCell, Cell* newCell) {
    
}

Game::~Game() {
    userList.clear();
    taskList.clear();
}
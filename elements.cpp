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
    coord[0]    = x;
    coord[1]    = y;
    status      = false;
    participant = NULL;
}

SensingTask::~SensingTask() {

}

Enviroment::Enviroment(int size) {    

}

void Enviroment::set(int numUsers, int numIncent) {

}

void Enviroment::placeEntity(Entity* newEntity) {

}

Cell* Enviroment::getCell(int x, int y) {

}

Enviroment::~Enviroment() {

}

Game::game() {

}

void Game::set() {

}

gameStatus Game::play() {
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

void Game::movUser(User* movingUser, Cell* oldCell, Cell* newCell) {
    
}

Game::~Game() {
    userList.clear();
    taskList.clear();
}
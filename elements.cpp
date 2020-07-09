#include "elements.hpp"

cell::cell(int travelCost) {
    int cost = travelCost;
}

void cell::addEntity(entity* enteringEntity) {
    
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

void cell::delEntity(entity* leavingEntity) {
    int size = entityVector.size();
    for(int i = 0; i < size; i++) {
        if(entityVector[i] == leavingEntity) {
            entityVector[i] = nullptr;
            return;
        }
    }
}

cell::~cell() {

}

user::user() {
    SID       = 0;
    opTime    = 0;
    opCost    = 0;
    distance  = 0;
    coord[0]  = -1;
    coord[1]  = -1;
    accReward = 0.0;
}

void user::set(int x, int y) {
    SID       = 0;
    opTime    = 0;
    opCost    = 0;
    distance  = 0;
    coord[0]  = x;
    coord[1]  = y;
    accReward = 0.0;
}

int user::getCoord(const char component) {
    switch(component) {
        case 'x':
            return coord[0];
            break;

        case 'y':
            return coord[1];
            break;
        
        default:
            bail(2, "Incorrect use of getCoord function");

    }
    cerr << "Warning, getCoord failed to return coord or error!" << endl;
    return -2;
}

int user::selectSID(sensingTask *sensingTaskList) {
    
}

user::~user() {

}

sensingTask::sensingTask(int indexSID, float incentive) {
    SID         = indexSID;
    coord[0]    = -1;
    coord[1]    = -1;
    status      = false;
    reward      = incentive;
    participant = NULL;
}

void sensingTask::set(int x, int y) {
    coord[0]    = x;
    coord[1]    = y;
    status      = false;
    participant = NULL;
}

int sensingTask::getCoord(const char component) {
    switch(component) {
        case 'x':
            return coord[0];
            break;

        case 'y':
            return coord[1];
            break;
        
        default:
            bail(2, "Incorrect use of getCoord function");

    }
    cerr << "Warning, getCoord failed to return coord or error!" << endl;
    return -2;
}

sensingTask::~sensingTask() {

}

enviroment::enviroment(int numIncent, int userNum, int boardSize, float preBudget, float percent) {    
    totalTime          = 0;
    totalIncentives    = numIncent;
    totalUsers         = userNum;
    size               = boardSize;
    predictedBudget    = preBudget;
    coveragePercentage = percent;
    
    userList.assign(totalUsers, user());

    for(int i = 0; totalIncentives > i; i++)
        taskList.push_back(sensingTask(i+1, preBudget/(float)numIncent));
}

void enviroment::shuffle() {

    

}

void enviroment::set() {
    totalTime = 0;

    int x = -1;
    int y = -1;

    /* 
    * performance evaulation:
    *   - nested for loops 
    *   - check all other users if coords match random generated overlap
    */
    for(int i = 0; totalUsers > i; i++) {  /* assume users cannot be on the same coordinates */

        x = rand()%size;      /* random x int component in range [0, size] */
        y = rand()%size;      /* random y int component in range [0, size] */

        for(int j = 0; totalUsers > j; j++) {   /* check every user if on same grid */
            if(i != j) {
                if ((userList[j].getCoord('x') == x) && (userList[j].getCoord('y') == y)) {
                    i--;
                    continue;
                }
            }
        }

        userList[i].set(rand()%size, rand()%size);
    }

    x = -1;
    y = -1;

    for(int i = 0; totalIncentives > i; i++) { /* assume incentives will not be on the same task */
        
        x = rand()%size;        /* random x int component in range [0, size] */
        y = rand()%size;        /* random y int component in range [0, size] */

        for(int j = 0; totalIncentives > j; j++) {      /* check every user if on same grid */
            if(i != j) {
                if ((taskList[j].getCoord('x') == x) && (taskList[j].getCoord('y') == y)) {
                    i--;
                    continue;
                }
            }
        }

        taskList[i].set(rand()%size, rand()%size);
    }

}

void enviroment::play() {
    /*
    * Outline:
    *   - at start, all users are randomly selected to select sensing task (shuffle)
    *   - each turn updates board stats
    *       -players can move on to the same space
    *   - game ends if there are only unavaliable users
    */

   

}

void enviroment::save() {

}

enviroment::~enviroment() {

}

game::game(){

}

void game::movUser(user* movingUser, cell oldCell, cell newCell) {
    
}

game::~game(){
    userList.clear();
    taskList.clear();
}
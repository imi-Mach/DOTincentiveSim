#include "elements.hpp"

Cell::Cell() {
    int cost = NULL;
    sensingTask = nullptr;
}

void Cell::set(int geoCost){
    cost = geoCost;
    if (!resVec.empty()) {
        resVec.clear();
    }
}

void Cell::setTask(SensingTask* task) {
    sensingTask = task;
}

void Cell::addUser(User* newUser) {
    
    int size;
    int i;

    /* empty vector case */
    if(resVec.empty()) {
        resVec.push_back(newUser);
        return;
    }

    size = resVec.size();

    /* scan through vector for NULL pointers */
    for(i = 0; i < size; i++) {
        if(resVec[i] == nullptr) {
            resVec[i] = newUser;
            return;
        }
    }

    /* vector is full, add another container */
    resVec.push_back(newUser);

}

void Cell::delUser(User* leavingUser) {
    int size = resVec.size();
    for(int i = 0; i < size; i++) {
        if(resVec[i] == leavingUser) {
            resVec[i] = nullptr;
            return;
        }
    }
}

int Cell::getCost(){
    return cost;
}

SensingTask* Cell::getTask() {
    return sensingTask;
}

vector<User*>* Cell::getResVec() {
    return &resVec;
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
    bail(2, "FATAL error: getCoord failed to return coord or error!");
    return -2;
}

int Entity::getSID() {
    return SID;
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

void User::set(int x_pos, int y_pos) {
    SID       = 0;
    x         = x_pos;
    y         = y_pos;
    opTime    = 0;
    opCost    = 0;
    distance  = 0;
    accReward = 0.0;
}

int User::selectSID(vector<SensingTask*>* sensingTaskList) {
    
}

void User::update(int cost, int distanceRemaing, int x_new, int y_new) {
    opTime   += 1;
    opCost   += cost;
    distance  = distanceRemaing;
    x         = x_new;
    y         = y_new;
}

void User::update(int SID, float reward) {
    SID = 0;
    accReward += reward;

}

User::~User() {

}

SensingTask::SensingTask(int indexSID, float incentive) {
    SID         = indexSID;
    x           = -1;
    y           = -1;
    status      = false;
    reward      = incentive;
    participant = nullptr;
}

void SensingTask::set(int x, int y) {
    x           = x;
    y           = y;
    status      = false;
    participant = nullptr;
}

void SensingTask::update(bool statusChange, User *userParticipant) {
    status = statusChange;
    participant = userParticipant;
}

float SensingTask::getReward() {
    return reward;
}

SensingTask::~SensingTask() {

}

Enviroment::Enviroment(int size) { 
    geoSetting = UNIFORM;

    vector<Cell> v;

    for(int i = 0; i < size; i++) {
        v.push_back(Cell());
    }

    for(int i = 0; i < size; i++) {
        grid.push_back(v);
    }

    /*
    for(int i = 0; i < size; i++)  {
        vector<Cell> v;
        for(int j = 0; j < size; j++) {
                v.push_back(Cell());
        }
        grid.push_back(v);
    }
    */
    
}

int Enviroment::assignCost(int x, int y) {
    switch(geoSetting) {
        case UNIFORM:       /* only case programmed */
            return 1;
        case SIMPLE:
            return 1;
        case COMPLEX:
            return 1;
        case RANDOM:
            return 1;
    }

    bail(2, "FATAL error: Geo cost was not properly set");
    return 1;
}

void Enviroment::set() {
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            grid[i][j].set(assignCost(i, j));
        }
    }
}

Cell* Enviroment::getCell(int x, int y) {
    
    Cell* cp;

    try {
        cp = &grid[x][y];
    }
    catch (const std::out_of_range& oor) {
        cerr << "Out of Range error (getCell: size = " << size << ", x = " << x << ", y = " << y << "): " << oor.what() << endl;
        exit(2);
    }

    return cp;
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

    User* up;
    SensingTask* stp;
    vector<User*> userVec;
    vector<SensingTask*> taskVec;

    state               = CONSTRUCTION;
    totalTime           = 0;
    totalIncentives     = numIncent;
    totalUsers          = numUser;
    totalDrops          = 0;
    finishedIncentives  = 0;
    boardSize           = size;
    preBudget           = predictedBudget;
    userList            = &userVec;
    taskList            = &taskVec;

    board = new Enviroment(boardSize);

    for(int i = 0; i < numUser; i++) {
        up = new User();
        userList->push_back(up);
        delete up;
    }

    for(int i = 0; i < numIncent; i++) {
        stp = new SensingTask(i+1, preBudget/((float) numIncent));
        taskList->push_back(stp);
        delete stp;
    }

}

void Game::capture(User* user) {
    int SID;
    SensingTask* stp;

    SID = user->getSID();
    stp =(*taskList)[SID];

    user->update(0, stp->getReward());
    stp->update(true, user);

}

int Game::step(User* movingUser,Cell* oldCell, const char option) {
    Cell* cp = nullptr;
    switch(option) {
        case 'l':
            oldCell->delUser(movingUser);
            cp = board->getCell(movingUser->getCoord('x')-1, movingUser->getCoord('y'));
            cp->addUser(movingUser);
            return cp->getCost();
            break;
        case 'r':
            oldCell->delUser(movingUser);
            cp = board->getCell(movingUser->getCoord('x')+1, movingUser->getCoord('y'));
            cp->addUser(movingUser);
            return cp->getCost();
            break;
        case 'u':
            oldCell->delUser(movingUser);
            cp = board->getCell(movingUser->getCoord('x'), movingUser->getCoord('y')+1);
            cp->addUser(movingUser);
            return cp->getCost();
            break;
        case 'd':
        oldCell->delUser(movingUser);
            cp = board->getCell(movingUser->getCoord('x'), movingUser->getCoord('y')-1);
            cp->addUser(movingUser);
            return cp->getCost();
            break;
    }
    
}

void Game::movUser(User* movingUser) {

    int cost;
    SensingTask* stp;
    stp = (*taskList)[movingUser->getSID()];

    int x_o = movingUser->getCoord('x');
    int y_o = movingUser->getCoord('y');

    int x_f = stp->getCoord('x');
    int y_f = stp->getCoord('y');

    int x_d = x_f - x_o;
    int y_d = y_f - y_o;

    if(abs(x_d) >= abs(y_d)) {
        if(x_d > 0) {
            cost = step(movingUser, board->getCell(x_o,y_o), 'r');
            movingUser->update(cost, x_d + y_d - 1, x_o+1, y_o);
            x_o += 1;
        }
        else if(x_d < 0) {
            cost = step(movingUser, board->getCell(x_o,y_o), 'l');
            movingUser->update(cost, x_d + y_d - 1, x_o-1, y_o);
            x_o -= 1;
        }
        else if((x_d == 0) && (y_d == 0)){
            capture(movingUser);
            movUser(movingUser);
            x_f = -1;
            y_f = -1;
        }
    }
    else if (abs(x_d) < abs(y_d)) {
        if(y_d > 0) {
            cost = step(movingUser, board->getCell(x_o,y_o), 'u');
            movingUser->update(cost, x_d + y_d - 1, x_o, y_o+1);
            y_o += 1;
        }
        else if(y_d < 0) {
            cost = step(movingUser, board->getCell(x_o,y_o), 'd');
            movingUser->update(cost, x_d + y_d - 1, x_o, y_o-1);
            y_o -= 1;
        }
    }

    if((x_o == x_f) && (y_o == y_f)) {
        capture(movingUser);
    }


}

void Game::set() {

    state               = INPROGRESS;
    totalTime           = 0;
    totalDrops          = 0;
    finishedIncentives  = 0;
    int x               = NULL;
    int y               = NULL;
    Cell* cp            = nullptr;

    srand(time(0));

    board->set();

    for(int i = 0; i < totalUsers; i++) {   /* possible infinte loop if x and y fail to be random */
        x = rand() % boardSize;
        y = rand() % boardSize;

        cp = board->getCell(x,y);

        if (!cp->getResVec()->empty()) {
            i--;
            continue;
        }
        (*userList)[i]->set(x,y);
        cp->addUser((*userList)[i]);
    }

    for(int i = 0; i < totalIncentives; i++) { /* possible infinte loop if x and y fail to be random */
        x = rand() % boardSize;
        y = rand() % boardSize;

        cp = board->getCell(x,y);

        if (cp->getTask() != nullptr) {  /* add condition to check if resList is empty to relate both */
            i--;
            continue;
        }
        (*taskList)[i]->set(x,y);
        cp->setTask((*taskList)[i]);
    }

}

void Game::play() {

    auto rng = default_random_engine {};
    int  SID = NULL;

    while(state == INPROGRESS) {
        shuffle((*userList).begin(), (*userList).end(), rng); /* users are randomized */

        for(int i = 0; i < totalUsers; i++) {           /* go through each user and update available users */
            
            SID = (*userList)[i]->getSID();

            if(SID == 0) {                              /* if SID == 0, then user goes through task selection process */
                (*userList)[i]->selectSID(taskList);
                i--;
                continue;
            }
            else if(SID > 0) {                          /* if SID > 0, then user moves. */
                movUser((*userList)[i]);
            }
        }

        if(totalDrops == totalUsers) {
            if(finishedIncentives == totalIncentives) {
                state = COMPLETE;
            }
            else if(finishedIncentives < totalIncentives) {
                state = USERSFAILED;
            }
            else {
                bail(3, "FATAL error: game state attepted to change undefined state.");
            }
        }
        
        totalTime++;
    }

}

void Game::save() {

}

void Game::reset() {

}


Game::~Game() {
    (*userList).clear();
    (*taskList).clear();
}
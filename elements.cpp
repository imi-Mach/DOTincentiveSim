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

void User::selectSID(Enviroment* board, vector<SensingTask*>* sensingTaskList, int numTasks) {
    /* 
     * User Selection Process + Dropout scheme:
     *  - look through each incentive and calculate predicted net marginal profit
     *  - 10% net profit margin threshold
     *  - (net profit margin %) = 100% * (profit) / (accReward)
     *                          = 100% * (reward - preCost) / (accReard)
     *  - use max value to find best option based on proximity (simple case)
     *  - if best option is lower than 10%, then the user drops
     */

    SensingTask* stp;
    int x_f;
    int y_f;
    int x_abs;
    int y_abs;
    int avgCost;        /* for more complex boards, this variable would need changing */
    int newSID;
    float temp_reward;
    float max_reward;
    float temp_profit;
    float max_profit;
    float nmp_thres; /* minimum acceptable net marginal profit threshold for user to accept task */
    float nmp;

    avgCost = board->getAvgCost();
    newSID = -1;
    temp_reward = 0;
    max_reward = 0;
    temp_profit = 0;
    max_profit = 0;

    for(int i = 0; i < numTasks; i++) {
        if((*sensingTaskList)[i]->getUser() == nullptr) {
            stp = (*sensingTaskList)[i];
            x_f = stp->getCoord('x');
            y_f = stp->getCoord('y');
            x_abs = abs(x_f - x);
            y_abs = abs(y_f - y);
            temp_reward = stp->getReward();
            temp_profit = temp_reward - (float)((x_abs + y_abs) * avgCost);

            if(temp_profit > max_profit) {
                max_reward = temp_reward;
                newSID = stp->getSID();
            }

        }

    }

    if(newSID == -1) {
        SID = -1;
        return;
    }

    if(accReward > 0) {
        nmp = 100.0 * max_profit / accReward;
    }
    else if(accReward == 0) {
        nmp = 100.0 * max_profit / max_reward;
    }

    if (nmp_thres < nmp) {
        SID = -1;
        return;
    }

    update(newSID, 0);
    (*sensingTaskList)[newSID]->update(false, this);

}

void User::update(int cost, int distanceRemaing, int x_new, int y_new) {
    opTime   += 1;
    opCost   += cost;
    distance  = distanceRemaing;
    x         = x_new;
    y         = y_new;
}

void User::update(int newSID, float reward) {
    SID = newSID;
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

User* SensingTask::getUser() {
    return participant;
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

int Enviroment::getAvgCost() {
    return avgCost;
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

    int cost;                                   /* cost of moving cell to cell */
    SensingTask* stp;                           /* sensingtask gives objective destination */
    stp = (*taskList)[movingUser->getSID()];    /* sensingtask is given by user */

    /* store x&y coords of user in local variables */
    int x_o = movingUser->getCoord('x');
    int y_o = movingUser->getCoord('y');

    /* store x&y coords of task in local variables */
    int x_f = stp->getCoord('x');
    int y_f = stp->getCoord('y');

    /* x&y displacement relative to the user and task */
    int x_d = x_f - x_o;
    int y_d = y_f - y_o;

    /* bias to move based on larger x or y displacement to reduce allocation in cells */
    if(abs(x_d) >= abs(y_d)) {                                      /* move in x direction */
        if(x_d > 0) {
            cost = step(movingUser, board->getCell(x_o,y_o), 'r');  /* move right */
            movingUser->update(cost, x_d + y_d - 1, x_o+1, y_o);
            x_o += 1;
        }
        else if(x_d < 0) {
            cost = step(movingUser, board->getCell(x_o,y_o), 'l');  /* move left */
            movingUser->update(cost, x_d + y_d - 1, x_o-1, y_o);
            x_o -= 1;
        }
        else if((x_d == 0) && (y_d == 0)){                          /* case if user starts on incentive */
            capture(movingUser);
            movUser(movingUser);
            x_f = -1;
            y_f = -1;
        }
    }
    else if (abs(x_d) < abs(y_d)) {                                 /* move in y direction */
        if(y_d > 0) {
            cost = step(movingUser, board->getCell(x_o,y_o), 'u');  /* move up */
            movingUser->update(cost, x_d + y_d - 1, x_o, y_o+1);
            y_o += 1;
        }
        else if(y_d < 0) {
            cost = step(movingUser, board->getCell(x_o,y_o), 'd');  /* move down */
            movingUser->update(cost, x_d + y_d - 1, x_o, y_o-1);
            y_o -= 1;
        }
    }

    /* check if user moved onto their incentive */
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
    User *up = nullptr; /* user pointer */

    while(state == INPROGRESS) {
        shuffle((*userList).begin(), (*userList).end(), rng); /* users are randomized */

        for(int i = 0; i < totalUsers; i++) {           /* go through each user and update available users */
            
            up = (*userList)[i];
            SID = up->getSID();

            if(SID == 0) {                              /* if SID == 0, then user goes through task selection process */
                up->selectSID(board, taskList, totalIncentives);
                i--;
                continue;
            }
            else if(SID > 0) {                          /* if SID > 0, then user moves. */
                movUser(up);
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


Game::~Game() {
    (*userList).clear();
    (*taskList).clear();
}
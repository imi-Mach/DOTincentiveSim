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
        case UNIFORM:  /* only case programmed */
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
    
    srand(time(0));

    Cell* cp;

    int x = NULL;
    int y = NULL;
    
    board->set();

    for(int i = 0; i < totalUsers; i++) {
        x = rand() % boardSize;
        y = rand() % boardSize;

        cp = board->getCell(x,y);

        if (!cp->getResVec()->empty()) {
            i--;
            continue;
        }
        userList[i].set(x,y);
        cp->addUser(&userList[i]);
    }

    for(int i = 0; i < totalIncentives; i++) {
        x = rand() % boardSize;
        y = rand() % boardSize;

        cp = board->getCell(x,y);

        if (cp->getTask() != nullptr) {
            i--;
            continue;
        }
        taskList[i].set(x,y);
        cp->setTask(&taskList[i]);
    }

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
#include "Game.hpp"

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

    state               = CONSTRUCTION;
    trialNum            = 0;
    totalTime           = 0;
    totalIncentives     = numIncent;
    totalUsers          = numUser;
    totalDrops          = 0;
    finishedIncentives  = 0;
    boardSize           = size;
    preBudget           = predictedBudget;

    userList            = new vector<User>;
    taskList            = new vector<SensingTask>;

    board = new Enviroment(boardSize);

    for(int i = 0; i < numUser; i++) {
        userList->push_back(User());
    }

    for(int i = 0; i < numIncent; i++) {
        taskList->push_back(SensingTask(i+1, preBudget/((float) numIncent)));
    }

}

void Game::capture(User* user) {
    int SID;
    SensingTask* stp;

    SID = user->getSID();
    stp = &(*taskList)[SID];

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
    stp = &(*taskList)[movingUser->getSID()];    /* sensingtask is given by user */

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

void Game::set(int round) {
    trialNum = round;
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
        (*userList)[i].set(x,y);
        cp->addUser(&(*userList)[i]);
    }

    for(int i = 0; i < totalIncentives; i++) { /* possible infinte loop if x and y fail to be random */
        x = rand() % boardSize;
        y = rand() % boardSize;

        cp = board->getCell(x,y);

        if (cp->getTask() != nullptr) {  /* add condition to check if resList is empty to relate both */
            i--;
            continue;
        }
        (*taskList)[i].set(x,y);
        cp->setTask(&(*taskList)[i]);
    }

}

void Game::play() {

    auto rng = default_random_engine {};
    int  SID = NULL;
    User *up = nullptr; /* user pointer */

    while(state == INPROGRESS) {
        shuffle((*userList).begin(), (*userList).end(), rng); /* users are randomized */

        for(int i = 0; i < totalUsers; i++) {           /* go through each user and update available users */
            
            up = &(*userList)[i];
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

void Game::save(ofstream* dataFile) {

    /* game info */
    string finGameState;

    /* enviroment info */
    int avgCostCell     = board->getAvgCost();

    /* user info */
    User *up            = nullptr;
    int sumOpTime       = 0;
    int sumOpCost       = 0;
    float sumAccReward  = 0.0;

    /* sensing task info */
    SensingTask *stp    = nullptr;
    int remainSTs       = 0;
    float missedRewards = 0.0;

    /* Data file info */
    const int gamestat_width = 6;
    const int intVal_width = 8;
    const int fltVal_width = 10;
    const int num_flds = 9 ;
    const string sep = " |" ;
    const int total_width = intVal_width*6 + gamestat_width + fltVal_width*2 + sep.size() * num_flds ;
    const string line = sep + std::string( total_width-1, '-' ) + '|' ;

    if(state == COMPLETE) {
        finGameState = "COMP";
    }
    else if(state == USERSFAILED) {
        finGameState = "FAIL";
    }
    else {
        finGameState = "ERR";
    }

    for(int i = 0; i < totalUsers; i++) {
        up = &(*userList)[i];
        sumOpTime    += up->getOpTime();
        sumOpCost    += up->getOpTime();
        sumAccReward += up->getAccReward();
    }

    remainSTs = 0;
    missedRewards = 0;

    for(int i = 0; i < totalIncentives; i++) {
        stp = &(*taskList)[i];
        if(!stp->getStatus()) {
            missedRewards = stp->getReward();
            remainSTs++;
        }
    }

    /*
     * Print order:
     *  - Game details: trialNum, gamestate, totalTime, avgCostCell, sumOpTime, sumOpCost, sumAccReward, remainSTs, missedRewards
     * 
     */

    if(trialNum == 1) {
        *dataFile << line << '\n' << sep
              << setw(intVal_width) << "Trial #" << sep << setw(gamestat_width) << "Result" << sep
              << setw(intVal_width) << "Sim Time" << sep << setw(intVal_width) << "AVG cost" << sep
              << setw(intVal_width) << "OP cost" << sep << setw(fltVal_width) << "Rewards($)" << sep
              << setw(intVal_width) << "ST Left" << sep << setw(fltVal_width) << "Surplus($)" << sep
              << '\n' << line << '\n' ;
    }

    *dataFile << line << '\n' << sep
              << setw(intVal_width) << trialNum << sep << setw(gamestat_width) << finGameState << sep
              << setw(intVal_width) << totalTime << sep << setw(intVal_width) << avgCostCell << sep
              << setw(intVal_width) << sumOpCost << sep<< fixed << setprecision(2) << setw(fltVal_width) << sumAccReward << sep
              << setw(intVal_width) << remainSTs << sep << setw(fltVal_width) << missedRewards << sep
              << '\n' << line << '\n' ;

}


Game::~Game() {

    board->~Enviroment();
    delete board;

    for(int i = 0; i < totalUsers; i++) {
        (*userList)[i].~User();
    }
    userList->clear();
    delete userList;

    for(int i = 0; i < totalIncentives; i++) {
        (*taskList)[i].~SensingTask();
    }
    taskList->clear();
    delete taskList;
    
}
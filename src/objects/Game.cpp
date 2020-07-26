#include "Game.hpp"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/*            Construction Phase:             */
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* Constructor */
Game::Game(Enviroment *enviroment, IM_t imType, int numIncent, int numUser, int size, float predictedBudget, bool verboseCheck) {
    /* Game constructor:
     *   - Responsible for initializing all variables
     *       - counter variables initialized
     *       - enviroment referenced
     *       - set of users constructed and pointed to
     *       - set of sensing tasks constructed and pointed to
     */

    srand(time(0)); /* random function set */
    
    im                  = imType;
    state               = CONSTRUCTION;
    staticFlag          = false;
    verbose             = verboseCheck;
    trialNum            = 0;
    totalTime           = 0;
    totalIncentives     = numIncent;
    totalUsers          = numUser;
    totalDrops          = 0;
    finishedIncentives  = 0;
    boardSize           = size;
    preBudget           = predictedBudget;

    avgWinRate = 0;
    avgSimTime = 0;
    avgOpCost  = 0;

    board = enviroment;
    
    for(int i = 0; i < numUser; i++) {
        userList.push_back(User(i+1));
    }

    for(int i = 0; i < numIncent; i++) {
        taskList.push_back(SensingTask(i+1, preBudget/((float) numIncent)));
    }

}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/*                Game Phase:                 */
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* Attribute manipulator method */
int Game::step(User* movingUser,Cell* oldCell, const char option) {
    /* user direction is defined in the cardinal directions */

    /* General Procedure:
     *  - Determine direction (option)
     *  - Remove user from current cell (delUser)
     *  - Calculate adjacent cell location (cp)
     *  - Add user to new cell resident list (addUser)
     */ 

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
    bail(3, "FATA error: Game::Step failed to select viable \"option\".");
    return -1;
    
}

/* Attribute manipulator method */
void Game::capture(User* user) {
    /* once a user moves onto an incentive the capture method updates stats */

    SensingTask* stp = &taskList[user->getSID()-1];
    user->update(0, stp->getFinReward());
    stp->update(true, user->getUID());
    finishedIncentives++;
}

/* Attribute manipulator method */
void Game::movUser(User* movingUser) {
    /* handles different cases of user position relative to ST */

    /* General Procedure:
     *  - Calculate distance between user and incentive
     *  - resolve which direction to travel
     *  - check if incentive was reached
     */

    int cost = 1;
    SensingTask* stp = &taskList[movingUser->getSID()-1];

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

/* Reset method */
void Game::set(int round) {
    /* all variables are reset for each trial */

    state               = INPROGRESS;
    trialNum            = round;
    totalTime           = 0;
    totalDrops          = 0;
    finishedIncentives  = 0;
    int x               = -1;
    int y               = -1;
    Cell* cp            = nullptr;

    board->set();

    /* users are randomly placed on grid with no overlap */
    for(int i = 0; i < totalUsers; i++) { 
        x = rng(boardSize);
        y = rng(boardSize);
        
        cp = board->getCell(x,y);
        
        if (!cp->getResVec()->empty()) {
            i--;
            continue;
        }
        userList[i].set(x,y);
        cp->addUser(&userList[i]);
    }
    
    /* ST are randomly placed on grid with no overlap (overlap with user is allowed) */
    for(int i = 0; i < totalIncentives; i++) {
        x = rng(boardSize);
        y = rng(boardSize);

        cp = board->getCell(x,y);

        if (cp->getTask() != nullptr) { 
            i--;
            continue;
        }
        taskList[i].set(x,y);
        cp->setTask(&taskList[i]);
    }
    
}

void Game::incentiveMechanism(User* user) {

    switch(im) {
        case S_UNIFORM: {
            if(staticFlag) return;
            staticFlag = true;

            for(int i = 0; i < totalIncentives; i++) {
                taskList[i].setReward(taskList[i].getBaseReward());
            }
            return;
            break;
        }
        case S_UNIFORM_TSP: {/* use modulo to create subsets */ 

        }
        case S_STCENTER: {
            if(staticFlag) return;
            staticFlag = true;
            
            SensingTask *stp = nullptr;
            int avg_x = 0;
            int avg_y = 0;
            int disp_x = 0;
            int disp_y = 0;
            int distance = 0;
            double ratio = 0;

            for(int i = 0; i < totalIncentives; i++) {
                avg_x += taskList[i].getCoord('x');
                avg_y += taskList[i].getCoord('y');
            }

            avg_x = (int)floor((double)avg_x / (double)totalIncentives);
            avg_y = (int)floor((double)avg_y / (double)totalIncentives);

            for (int i = 0; i < totalIncentives; i++) {
                stp = &taskList[i];
                disp_x = abs(stp->getCoord('x') - avg_x);
                disp_y = abs(stp->getCoord('y') - avg_y);
                distance = disp_x + disp_y;
                ratio = (((double)distance) / ((double)(2 * boardSize)))/2; /* 0.0-50.0 range */
                stp->setReward((float)(1-ratio) * stp->getBaseReward());
            }

            return;
            break;
        }
        case S_USERCENTER: {        /* rewards need to be associated to user */
            if(staticFlag) return;
            staticFlag = true;

            SensingTask *stp = nullptr;
            int avg_x = 0;
            int avg_y = 0;
            int disp_x = 0;
            int disp_y = 0;
            int distance = 0;
            double ratio = 0;

            for(int i = 0; i < totalUsers; i++) {
                avg_x += userList[i].getCoord('x');
                avg_y += userList[i].getCoord('y');
            }

            avg_x = (int)floor((double)avg_x / (double)totalUsers);
            avg_y = (int)floor((double)avg_y / (double)totalUsers);
            
            for (int i = 0; i < totalIncentives; i++) {
                stp = &taskList[i];
                disp_x = abs(stp->getCoord('x') - avg_x);
                disp_y = abs(stp->getCoord('y') - avg_y);
                distance = disp_x + disp_y;
                ratio = (((double)distance) / ((double)(2 * boardSize)))/2; /* 0.0-50.0 range */
                stp->setReward((float)(1-ratio) * stp->getBaseReward());
            }
            return;
            break;
        }

        case D_RELATIVE: {
            SensingTask* stp = nullptr;
            User* up = nullptr;
            vector<int> distance(totalUsers, 0);
            int counter = 0;
            int place   = 1;
            int userDistance;

            for(int i = 0; i < totalIncentives; i++) {
                if((stp = &taskList[i])->getUID() > 0) {
                    continue;
                }
                for(int j = 0; j < totalUsers; j++) {
                    up = &userList[j];
                    if(up->getSID() > 0) {
                        distance[j]  = userList[j].getDistance();
                        distance[j] += (abs(stp->getCoord('x') - taskList[up->getSID() - 1].getCoord('x')) + abs(stp->getCoord('y') - taskList[up->getSID() - 1].getCoord('y')));
                    }
                    else if(up->getSID() == 0) {
                        distance[j] = (abs(stp->getCoord('x') - up->getCoord('x')) + abs(stp->getCoord('y') - up->getCoord('y')));
                    }
                    else if(up->getSID() == -1) {
                        distance[j] = 0;
                    }
                }
                userDistance = distance[user->getUID()-1];
                while(counter < totalUsers) {
                    if(userDistance > distance[counter]) {
                        place++;
                    }
                    counter++;
                }

                if(place == 1) stp->setReward(stp->getBaseReward());
                else stp->setReward(stp->getBaseReward() * (1.0 - 0.5 * ((place)/totalUsers)));
                
                place = 1;
                counter = 0;
                for(int j = 0; j < totalUsers; j++) distance[j] = 0;
            }
            return;
            break;
        }

        case D_UNIFORM_TSP: {
            /* first create edge matrix */

            vector<vector<int> > vec( boardSize , vector<int> (boardSize, 0));

            return;
            break;
        }

        case D_STREAK: {
            return;
            break;
        }

    }

}

/* Attribute manipulator method */
void Game::play() {
    /* each trial this method facilitates the "game" */

    /*
     * General Purpose:
     *  - Time based seed is generated for user random selection
     *  - Random number generator (rng) is defined for shuffle function
     *  - Game starts:
     *      - users are shuffled then sequentially selected
     *      - SID of current user dictates users next action
     *      - game ends when dropout condition is met (all users have dropped out)
     *  - Game termination:
     *      - IF dropout condition, and no ST, then game was successful
     *      - IF dropout condition, but there is/are ST(s), then game was a failure
     */
    
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    auto rng      = default_random_engine(seed);
    int  SID      = 0;
    User *up      = nullptr; /* up = user pointer */
    
    while(state == INPROGRESS) {

        shuffle(userList.begin(), userList.end(), rng); /* users are randomized */
        
        for(int i = 0; i < totalUsers; i++) {           /* go through each user and update available users */
            
            up  = &userList[i];
            SID = up->getSID();

            if(SID == 0) {                              /* if SID == 0, then user goes through task selection process */
                incentiveMechanism(up);
                up->selectSID(board, &taskList, totalIncentives);
                if(up->getSID() == -1) {
                    totalDrops++;
                }
                i--;
                continue;
            }
            else if(SID > 0) {                          /* if SID > 0, then user moves. */
                movUser(up);
            }

        }
        
        #ifdef DEBUG

        int k = 0;

        for(int i = 0; i < boardSize; i++) {
            for(int j = 0; j < boardSize; j++) {
                k = 0;
                for(; k < totalUsers; k++) {
                    if((userList[k].getCoord('x') == i) && (userList[k].getCoord('y') == j)) {
                        //cout << "[" << userList[k].getCoord('x') << "," << userList[k].getCoord('y') << "]";
                        cout << "i ";
                        break;
                    }

                }
                if((k == totalUsers) && (board->getCell(i,j)->getTask() != nullptr)) {
                    if (!board->getCell(i,j)->getTask()->getStatus()) {
                        cout << "S ";
                    }
                    else cout << "  ";
                }
                else if(k == totalUsers) {
                    cout << "  ";
                }
            }
            cout << endl;
        }
        
        cout << "-------------------" << endl;

        this_thread::sleep_for(std::chrono::milliseconds(500));

        #endif

        /* dropout condition */
        if(totalDrops == totalUsers) {

            /* update termination condition */
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

/* Save data method */
void Game::save(ofstream* dataFile) {

    User *up            = nullptr;
    double sumAccReward  = 0.0;
    double sumOpCost = 0;
    double factor = ((double)(trialNum-1)/((double)trialNum));
    
    for(int i = 0; i < totalUsers; i++) {
        up = &userList[i];
        sumOpCost += (double) userList[i].getOpTime();
        sumAccReward += up->getAccReward();
    }

    if(state == COMPLETE) {
        avgWinRate = avgWinRate * factor + 1.0/(double)trialNum;
    }
    else {
        avgWinRate = avgWinRate * factor;
    }

    avgSimTime = avgSimTime * factor + totalTime/(double)trialNum;

    avgOpCost = avgOpCost * factor + sumOpCost/(double)trialNum;

    if(verbose) {
        /* game info */
        string finGameState = "";

        /* enviroment info */
        int avgCostCell     = board->getAvgCost();

        /* sensing task info */
        SensingTask *stp    = nullptr;
        int remainSTs       = 0;
        float missedRewards = 0.0;

        /* Data format info */
        const int gamestat_width = 6;
        const int intVal_width = 8;
        const int fltVal_width = 10;
        const int num_flds = 9 ;
        const string sep = " |" ;
        const int total_width = intVal_width*5 + gamestat_width + fltVal_width*4 + sep.size() * num_flds ;
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

        for(int i = 0; i < totalIncentives; i++) {
            stp = &taskList[i];
            if(!stp->getStatus()) {
                missedRewards += stp->getReward();
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
                << setw(fltVal_width) << "OP cost" << sep << setw(fltVal_width) << "Rewards($)" << sep  << setw(fltVal_width) << "Surplus($)" << sep
                << setw(intVal_width) << "ST Left" << sep << setw(fltVal_width) << "Surplus($)" << sep
                << '\n' << line << '\n' ;
        }

        *dataFile << sep
                << setw(intVal_width) << trialNum << sep << setw(gamestat_width) << finGameState << sep
                << setw(intVal_width) << totalTime << sep << setw(intVal_width) << avgCostCell << sep
                << setw(fltVal_width) << sumOpCost << sep << fixed << setprecision(2) << setw(fltVal_width) << sumAccReward << sep
                << setw(fltVal_width) << (preBudget -sumAccReward) << sep
                << setw(intVal_width) << remainSTs << sep << (preBudget - sumAccReward) << sep
                << '\n' << line << endl;
    }

}

void Game::summary(ofstream* dataFile) {
    if(verbose) {
        *dataFile << "\n Summary data:\n";
        *dataFile << "ORDER: Win Rates, Simulation Time, Operation Cost\n";
    }
    *dataFile << avgWinRate << ' ' << avgSimTime << ' ' << avgOpCost << endl;
}

/* Destructor */
Game::~Game() {

}
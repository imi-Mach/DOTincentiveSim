#ifndef GAME
#define GAME

#include <vector>
#include <algorithm>        /* shuffle algorithm for random user selection*/
#include <random>           /* seed + generator for shuffle */
#include <chrono>
#include <fstream>
#include <iomanip>
#include "Cell.hpp"
#include "User.hpp"
#include "SensingTask.hpp"
#include "Enviroment.hpp"
#include "functions.h"


enum gameStatus {
    CONSTRUCTION,
    INPROGRESS,
    COMPLETE,
    USERSFAILED
};

class Game {
    public:
        Game(int, int, int, float);     /* constructs enviroment -> constructs users and sensing tasks */
        int  step(User*, Cell*, char);
        void capture(User*);
        void movUser(User*);            /* parameter desc: user moving, source, destination */
        void set(int);                     /* reset board to inital conditions */
        void play();                    /* play game */
        void save(ofstream*);
        ~Game();
    private:
        gameStatus state;
        int trialNum;
        int totalTime;
        int totalIncentives;
        int totalUsers;
        int totalDrops;
        int finishedIncentives;
        int boardSize;
        float preBudget;
        Enviroment* board;
        vector<User> userList;            /* c): */
        vector<SensingTask> taskList;     /* c): */

};

#endif
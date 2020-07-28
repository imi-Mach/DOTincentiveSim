#ifndef GAME
#define GAME

#include <unordered_map>
#include <vector>           /* allocations for user and ST lists, and other vector methods */
#include <algorithm>        /* shuffle algorithm for random user selection*/
#include <random>           /* seed + generator for shuffle */
#include <chrono>           /* debugging purposes when displaying turns */
#include <thread>           /* debugging purposes when displaying turns */
#include <fstream>          /* file for storing game results */
#include <iomanip>          /* printing formats for storing results */
#include "Cell.hpp"         /* definition of cell */
#include "User.hpp"         /* definition of user */
#include "SensingTask.hpp"  /* definition of ST */
#include "Enviroment.hpp"   /* definition of enviroment */
#include "functions.h"      /* bail function */

enum IM_t {
    S_UNIFORM,
    S_STCENTER,
    S_USERCENTER,
    D_STCENTER,
    D_USERCENTER,
    D_PREDICT,
    D_RELATIVE,
    D_TSP,
    D_GROUP_TSP,
    D_GROUP_PREDICT,
    D_STREAK
};

enum gameStatus {           /* different states of game */
    CONSTRUCTION,
    INPROGRESS,
    COMPLETE,
    USERSFAILED
};

class Game {                /* Game class maintains crucial information about structure of simulation */
    public:
        Game(Enviroment*, IM_t, int, int, int, float, bool); /* func desc: IN: current enviroment, number of incentives, number of users, board size, predicted budget. OUT: initialized game. */
        int  step(User*, Cell*, char);           /* func desc: IN: moving user, current cell, direction.                                                    OUT: cost of moving. */
        void capture(User*);                     /* func desc: IN: User ptr capturing ST.                                                                   OUT: n/a. */
        void movUser(User*);                     /* func desc: IN: User ptr for moving user.                                                                OUT: n/a. */
        void set(int);                           /* func desc: IN: trial number.                                                                            OUT: n/a. */
        void incentiveMechanism(User*);
        void play();                             /* func desc: IN: set game.                                                                                OUT: finished game. */
        void save(ofstream*);                    /* func desc: IN: file to save data too.                                                                   OUT: n/a. */
        void summary(ofstream*);                 /* func desc: IN: file to save summary data.                                                               OUT: n/a. */
        ~Game();
    private:
        IM_t im;
        gameStatus state;                        /* var desc: current game state: CONSTRUCTION, INPROGRESS, COMPLETE, or USERSFAILED */
        bool staticFlag;
        bool verbose;                            /* var desc:  */
        int trialNum;                            /* var desc: current trial */
        int totalTime;                           /* var desc: counter starts at 0 and ends when state changes from INPROGRESS */
        int totalIncentives;                     /* var desc: number of ST for trial */
        int totalUsers;                          /* var desc: number of users for trial */
        int totalDrops;                          /* var desc: current number of droped users */
        int finishedIncentives;                  /* var desc: current number of finished incentives*/
        int boardSize;                           /* var desc: side length of square board */
        float preBudget;                         /* var desc: predicted budget */
        double avgWinRate;                        /* var desc: avg success rate */
        double avgSimTime;                        /* var desc: avg simulation time */
        double avgOpCost;                         /* var desc: avg operation cost */
        double avgSurplus;
        Enviroment* board;                       /* var desc: enviroment created for game */
        vector<vector<int>> STdistanceMatrix;
        vector<User> userList;                   /* var desc: physical list of users that is referenced by methods */
        vector<SensingTask> taskList;            /* var desc: physical list of ST that is referenced by methods*/

};

#endif 
#ifndef ELEMENTS
#define ELEMENTS

#include "functions.h"
#include <vector>           /* 2-d grid of cells, user, and sensing task vectors */
#include <algorithm>        /* shuffle algorithm for random user selection*/
#include <random>           /* seed + generator for shuffle */
#include <cstdlib>
#include <ctime>
#include <stdexcept>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

class Cell {
    public:
        Cell();
        void set(int);
        void setTask(SensingTask*);
        void addUser(User*);                  /* parameter desc: */
        void delUser(User*);                  /* parameter desc: */
        int getCost();
        SensingTask* getTask();
        vector<User*>* getResVec();           /* parameter desc: */
        ~Cell();
    private:
        int cost;                             /* var desc: cost of moving cell to cell  */
        SensingTask* sensingTask;
        vector<User*>* resVec;                 /* var desc: resident list */
};

class Entity {
    public:
        void setCoord(const char, int);
        int  getCoord(const char);
        int  getSID();
    protected:
        int SID;            /* set(): */
        int x;
        int y;

};

class User : public Entity {
    public:
        User();                                                     /* construct phase:  */
        void  set(int, int);
        void  selectSID(Enviroment*, vector<SensingTask>*, int);    /* decide what the SID is */
        void  update(int, int, int, int);                            /* move update */
        void  update(int, float);                                    /* incentive capture update */
        int   getOpTime();
        int   getOpCost();
        float getAccReward();
        ~User();
    private:
        int opTime;         /* set(): */
        int opCost;         /* set(): */
        int distance;       /* set(): */
        float accReward;    /* set(): */
};

class SensingTask : public Entity {
    public:
        SensingTask(int, float);    /* construct phase: */
        void  set(int, int);
        void  update(bool, User*);
        bool  getStatus();
        float getReward();
        User *getUser();
        ~SensingTask();
    private:
        bool  status;                /* c): true = finished, false = not finished */
        float reward;               /* c): */
        User *participant;          /* c): */

};

enum boardType {
    UNIFORM,
    SIMPLE,
    COMPLEX,
    RANDOM
};

class Enviroment {
    public:
        Enviroment(int);                /* parameter desc: sideLength of square board */
        int assignCost(int, int);       /* parameter desc: assign geo cost based on x-y coords */
        int getAvgCost();
        void set();                     /* parameter desc:  */
        Cell* getCell(int, int);        /* parameter desc: x coord and y coord for entity placement */
        ~Enviroment();
    private:
        boardType geoSetting;
        int avgCost;
        int size;                         /* c): */
        vector< vector<Cell> >* grid;      /* c): 2d map of cells */

};

enum gameStatus {
    CONSTRUCTION,
    INPROGRESS,
    COMPLETE,
    USERSFAILED
};

class Game {
    public:
        Game(int, int, int, float);     /* constructs enviroment -> constructs users and sensing tasks */
        void capture(User*);
        int  step(User*, Cell*, char);
        void movUser(User*);            /* parameter desc: user moving, source, destination */
        void set(int);                     /* reset board to inital conditions */
        void play();                    /* play game */
        void save(ofstream*);
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
        vector<User>* userList;            /* c): */
        vector<SensingTask>* taskList;     /* c): */

};

#endif
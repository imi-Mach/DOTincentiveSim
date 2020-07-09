#ifndef ELEMENTS
#define ELEMENTS

#include "functions.hpp"
#include <vector>

using namespace std;

class cell {
    public:
        cell(int);
        void addEntity(entity*);                  /* parameter desc: add new entity pointer to cell's occupany list*/
        void delEntity(entity*);                  /* parameter desc: */
        vector<entity*>* getEntityVector();       /* parameter desc: */
        ~cell();
    private:
        int cost;                                 /* var desc: cost of moving cell to cell  */
        vector<entity*> entityVector;             /* var desc: occupancy list */
};

class entity {
    public:
        void setCoord(char, int);
        void getCoord(char);
    private:
        int SID;            /* set(): */
        int x;
        int y;

};

class user : public entity {
    public:
        user();                             /* construct phase:  */
        int  selectSID(sensingTask *);      /* decide what the SID is */
        ~user();
    private:
        int SID;            /* set(): */
        int opTime;         /* set(): */
        int opCost;         /* set(): */
        int distance;       /* set(): */
        float accReward;    /* set(): */
};

class sensingTask : public entity {
    public:
        sensingTask(int, float);    /* construct phase: */
        ~sensingTask();
    private:
        int SID;                    /* c):  */
        int coord[2];              /* set(): */
        bool status;                /* c): true = finished, false = not finished */
        float reward;               /* c): */
        user *participant;          /* c): */

};

class enviroment {
    public:
        enviroment(int, int, int, float, float);
        void shuffle();
        void set();
        void play();
        void save();
        ~enviroment();
    private:
        int curIncentives;                /* c): */
        int curUsers;                     /* c): */
        int size;                         /* c): */
        vector<user> userList;            /* c): */
        vector<sensingTask> taskList;     /* c): */

};

enum gameStatus {
    INPROGRESS,
    COMPLETE,
    USERSFAILED,
};

class game {
    public:
        game();                 /* constructs enviroment -> constructs users and sensing tasks */
        void set();         /* reset board to inital conditions */
        gameStatus play();      /* play game */
        void save();
        void movUser(user*, cell, cell);          /* parameter desc: user moving, source, destination */
    private:
        gameStatus state;
        int totalTime;
        int totalIncentives;
        int totalUsers;
        int boardSize;
        float preBudget;
        float coveragePercentage;


};

#endif

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
        bool status;                /* c): true = finished, false = not finished */
        float reward;               /* c): */
        user *participant;          /* c): */

};

class enviroment {
    public:
        enviroment(int);            /* parameter desc: sideLength of square board */
        void set(int, int);         /* parameter desc: num of users, num of incentives */
        void placeEntity(entity*);  /* parameter desc: reference for entity to assign to cell */
        cell* getCell(int, int);    /* parameter desc: x coord and y coord */
        ~enviroment();
    private:
        vector< vector<cell> > grid;      /* c): 2d map of cells */
        int size;                         /* c): */

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
        vector<user> userList;            /* c): */
        vector<sensingTask> taskList;     /* c): */

};

#endif

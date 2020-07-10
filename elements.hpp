#ifndef ELEMENTS
#define ELEMENTS

#include "functions.hpp"
#include <vector>

using namespace std;

class Cell {
    public:
        Cell(int);
        void addEntity(Entity*);                  /* parameter desc: add new entity pointer to cell's occupany list*/
        void delEntity(Entity*);                  /* parameter desc: */
        vector<Entity*>* getEntityVector();       /* parameter desc: */
        ~Cell();
    private:
        int cost;                                 /* var desc: cost of moving cell to cell  */
        vector<Entity*> entityVector;             /* var desc: occupancy list */
};

class Entity {
    public:
        void setCoord(const char, int);
        int getCoord(const char);
    protected:
        int SID;            /* set(): */
        int x;
        int y;

};

class User : public Entity {
    public:
        User();                             /* construct phase:  */
        void set(int, int);
        int  selectSID(SensingTask *);      /* decide what the SID is */
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
        void set(int, int);
        ~SensingTask();
    private:
        bool status;                /* c): true = finished, false = not finished */
        float reward;               /* c): */
        User *participant;          /* c): */

};

class Enviroment {
    public:
        Enviroment(int);            /* parameter desc: sideLength of square board */
        void set(int, int);         /* parameter desc: num of users, num of incentives */
        void placeEntity(Entity*);  /* parameter desc: reference for entity to assign to cell */
        Cell* getCell(int, int);    /* parameter desc: x coord and y coord for entity placement */
        ~Enviroment();
    private:
        vector< vector<Cell> > *grid;      /* c): 2d map of cells */
        int size;                         /* c): */

};

enum gameStatus {
    CONSTRUCTION,
    INPROGRESS,
    COMPLETE,
    USERSFAILED,
};

class Game {
    public:
        Game(int, int, int, float);                 /* constructs enviroment -> constructs users and sensing tasks */
        void set();         /* reset board to inital conditions */
        void play();      /* play game */
        void save();
        void reset();
        void movUser(User*, Cell*, Cell*);          /* parameter desc: user moving, source, destination */
    private:
        gameStatus state;
        int totalTime;
        int totalIncentives;
        int totalUsers;
        int boardSize;
        float preBudget;
        Enviroment *board;
        vector<User> userList;            /* c): */
        vector<SensingTask> taskList;     /* c): */

};

#endif

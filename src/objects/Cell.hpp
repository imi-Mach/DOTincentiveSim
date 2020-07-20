#ifndef CELL
#define CELL

#include <vector>           /* dynamic memory needed for residence list of users */
#include "User.hpp"         /* definition of users */
#include "SensingTask.hpp"  /* definition of ST */

class User;
class SensingTask;

class Cell {                         /* Cells are nodes used to construct envrioment graph */
    public:
        Cell();                      /* func desc: IN: n/a.                       OUT: initialized cell */
        void set(int);               /* func desc: IN: geographical based cost.   OUT: n/a*/
        void setTask(SensingTask*);  /* func desc: IN: ST pointer update.         OUT: n/a */
        void addUser(User*);         /* func desc: IN: User ptr moving into cell. OUT: n/a*/
        void delUser(User*);         /* func desc: IN: User ptr leaving cell.     OUT: n/a */
        int getCost();               /* func desc: IN: n/a.                       OUT: geographial cost */
        SensingTask* getTask();      /* func desc: IN: n/a.                       OUT: assigned ST*/
        vector<User*>* getResVec();  /* func desc: IN: n/a.                       OUT: resident user vector */
        ~Cell();
    private:
        int cost;                    /* var desc: cost of moving cell to cell.  */
        SensingTask* sensingTask;    /* var desc: reference to assigned ST, OR nullptr == no ST. */
        vector<User*> resVec;        /* var desc: resident list of users, can contain nullptr. */
};

#endif
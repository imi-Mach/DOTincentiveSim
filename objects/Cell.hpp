#ifndef CELL
#define CELL

#include <vector>
#include "User.hpp"
#include "SensingTask.hpp"

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

#endif
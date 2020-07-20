#ifndef USER
#define USER

#include "Entity.hpp"       /* definition of entity */
#include "SensingTask.hpp"  /* definition of sensing task */
#include "Enviroment.hpp"   /* definition of enviroment*/

class SensingTask;
class Enviroment;

class User : public Entity {    /* User class is derived from entity and represents users in the enviroment */
    public:
        User();                                                  /* func desc: IN: n/a.                                                               OUT: initilized user.  */
        void  set(int, int);                                     /* func desc: IN: x, and y coordinate for user to be set.                            OUT: n/a. */
        void  selectSID(Enviroment*, vector<SensingTask>*, int); /* func desc: IN: reference to enviroment, reference to list of ST, number of tasks. OUT: n/a. */
        void  update(int, int, int, int);                        /* func desc: IN: cost of travel, distance left, new x position, new y position.     OUT: n/a. */
        void  update(int, float);                                /* func desc: IN: changed SID, reward for capturing ST.                              OUT: n/a. */
        int   getOpTime();                                       /* func desc: IN: n/a.                                                               OUT: operation time.  */
        int   getOpCost();                                       /* func desc: IN: n/a.                                                               OUT: operation cost.  */
        float getAccReward();                                    /* func desc: IN: n/a.                                                               OUT: accumulated reward.  */
        ~User();
    private:
        int opTime;         /* var des: operation time starts with simulation and ends on dropout condition in selectSID() */
        int opCost;         /* var des: operation cost starts with simulation and ends on final cost added (updates on movements)*/
        int distance;       /* var des: remaining distance from sensing task */
        float accReward;    /* var des: accumulated reward for collecting incentives from sensing tasks */
};

#endif
#ifndef TASK
#define TASK

#include "Entity.hpp" /* Definition of entity */
#include "User.hpp"   /* Definition of user */

class User;

class SensingTask : public Entity {     /* ST class is derived from entity and are assigned to available users */
    public:
        SensingTask(int, float);   /* func desc: IN: SID assigned, reward for completion.   OUT: initialized ST. */
        void  set(int, int);       /* func desc: IN: x, and y coordinates.                  OUT: n/a. */
        void  update(bool, User*); /* func desc: IN: status of ST, and user participating.  OUT: n/a. */
        bool  getStatus();         /* func desc: IN: n/a.                                   OUT: current ST status. */
        float getReward();         /* func desc: IN: n/a.                                   OUT: reward for completion. */
        User *getUser();           /* func desc: IN: n/a.                                   OUT: participant of ST. */
        ~SensingTask();            /* func desc: IN: . OUT: . */
    private:
        bool  status;               /* var desc: true = finished, false = not finished */
        float reward;               /* var desc: reward for completion based on predicted budget */
        User *participant;          /* var desc: reference to participating user */

};

#endif
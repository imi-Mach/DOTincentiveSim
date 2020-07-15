#ifndef TASK
#define TASK

#include "Entity.hpp"
#include "User.hpp"

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

#endif
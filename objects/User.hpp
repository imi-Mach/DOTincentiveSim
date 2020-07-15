#ifndef USER
#define USER

#include "Entity.hpp"
#include "SensingTask.hpp"
#include "Enviroment.hpp"

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

#endif
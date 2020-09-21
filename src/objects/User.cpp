#include "User.hpp"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/*            Construction Phase:             */
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* Constructor */
User::User(int newUID) {
    /* initialized all members */

    SID       = 0;
    x         = -1;
    y         = -1;
    UID       = newUID;
    opTime    = 0;
    opCost    = 0;
    distance  = 0;
    accReward = 0.0;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/*                Game Phase:                 */
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* Reset method */
void User::set(int x_pos, int y_pos) {
    /* reset the members for new trial with random valid coordinates inside of the enviroment */

    SID       = 0;
    x         = x_pos;
    y         = y_pos;
    opTime    = 0;
    opCost    = 0;
    distance  = 0;
    accReward = 0.0;
}

/* Attribute manipulator method */
void User::selectSID(Enviroment* board, vector<SensingTask>* sensingTaskList, int numTasks) {
    /* 
     * User Selection Process + Dropout scheme:
     *  - look through each incentive and calculate predicted net marginal profit
     *  - 10% net profit margin threshold
     *  - (net profit margin %) = 100% * (profit) / (accReward)
     *                          = 100% * (reward - preCost) / (accReward)
     *  - if accReward is 0 (first sensing task), then accReward == reward of task on compeletion
     *  - use max value to find best option based on proximity (simple case)
     *  - if best option is lower than 10%, then the user drops
     */
    SensingTask* stp;
    int x_f             = 0;
    int y_f             = 0;
    int x_abs           = 0;
    int y_abs           = 0;
    int avgCost         = board->getAvgCost(); /* for more complex boards, this variable would need changing */
    int newSID          = -1;
    float temp_reward   = 0;
    float max_reward    = 0;
    float temp_profit   = 0;
    float max_profit    = 0;
    float nmp_thres     = 100; /* minimum acceptable net marginal profit threshold for user to accept task */
    float nmp           = 0;    

    for(int i = 0; i < numTasks; i++) {                     /* maximum reward finding algorithm */
        if((*sensingTaskList)[i].getUID() == 0) {
            stp = &(*sensingTaskList)[i];
            x_f = stp->getCoord('x');
            y_f = stp->getCoord('y');
            x_abs = abs(x_f - x);
            y_abs = abs(y_f - y);
            temp_reward = stp->getReward();
            temp_profit = temp_reward - (float)((x_abs + y_abs) * avgCost);
            if(temp_profit > max_profit) {
                max_reward = temp_reward;
                max_profit = temp_profit;
                newSID = stp->getSID();
            }

        }

    }

    /* if not tasks remain then user SID = -1 and dropout condition occurs */
    if(newSID == -1) {
        SID = -1;
        return;
    }
 
    /* calculation for net marginal profit */
    if(accReward > 0) {
        nmp = 100.0 * (max_profit + accReward) / accReward;
    }
    else if(accReward == 0) {    /* calculation if accReward is undefined */
        nmp = 100.0 * (max_profit + max_reward) / max_reward; //max_reward / max_reward;
    }

    /* if threshold is not surpased then dropout condition occurs */
    //cout << "[" << UID << "] : nmp = " << nmp << endl;
    if (nmp_thres > nmp) {
        SID = -1;
        return;
    }

    /* if all test pass, then user is assigned ST with SID equal to newSID */
    SID = newSID;
    (*sensingTaskList)[newSID-1].setFinReward((*sensingTaskList)[newSID-1].getReward());
    (*sensingTaskList)[newSID-1].update(false, UID);

}

/* Attribute set method */
void User::update(int cost, int distanceRemaing, int x_new, int y_new) {
    /* when the user moves the position and operation counters must be updated */

    opTime   += 1;
    opCost   += cost;
    distance  = distanceRemaing;
    x         = x_new;
    y         = y_new;
}

/* Attribute set method */
void User::update(int newSID, float reward) {
    /* when the user captures a ST then the SID must be updated and reward must be added */

    SID        = newSID;
    accReward += reward;
    distance   = 0;

}

/* Attribute get method */
int User::getOpTime() {
    return opTime;
}

/* Attribute get method */
int User::getOpCost() {
    return opCost;
}

int User::getDistance() {
    return distance;
}

/* Attribute get method */
float User::getAccReward() {
    return accReward;
}

/* Deconstructor */
User::~User() {

}
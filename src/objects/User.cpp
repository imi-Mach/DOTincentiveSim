#include "User.hpp"

User::User() {
    SID       = 0;
    x         = -1;
    y         = -1;
    opTime    = 0;
    opCost    = 0;
    distance  = 0;
    accReward = 0.0;
}

void User::set(int x_pos, int y_pos) {
    SID       = 0;
    x         = x_pos;
    y         = y_pos;
    opTime    = 0;
    opCost    = 0;
    distance  = 0;
    accReward = 0.0;
}

void User::selectSID(Enviroment* board, vector<SensingTask>* sensingTaskList, int numTasks) {
    /* 
     * User Selection Process + Dropout scheme:
     *  - look through each incentive and calculate predicted net marginal profit
     *  - 10% net profit margin threshold
     *  - (net profit margin %) = 100% * (profit) / (accReward)
     *                          = 100% * (reward - preCost) / (accReard)
     *  - use max value to find best option based on proximity (simple case)
     *  - if best option is lower than 10%, then the user drops
     */
    SensingTask* stp;
    int x_f             = 0;
    int y_f             = 0;
    int x_abs           = 0;
    int y_abs           = 0;
    int avgCost         = board->getAvgCost();        /* for more complex boards, this variable would need changing */
    int newSID          = -1;
    float temp_reward   = 0;
    float max_reward    = 0;
    float temp_profit   = 0;
    float max_profit    = 0;
    float nmp_thres     = 10; /* minimum acceptable net marginal profit threshold for user to accept task */
    float nmp           = 0;    

    for(int i = 0; i < numTasks; i++) {
        if((*sensingTaskList)[i].getUser() == nullptr) {
            stp = &(*sensingTaskList)[i];
            x_f = stp->getCoord('x');
            y_f = stp->getCoord('y');
            x_abs = abs(x_f - x);
            y_abs = abs(y_f - y);
            temp_reward = stp->getReward();
            temp_profit = temp_reward - (float)((x_abs + y_abs) * avgCost);
            //cout << "Sensing Task[" << i << "] temp_profit: " << temp_profit << endl;
            if(temp_profit > max_profit) {
                max_reward = temp_reward;
                max_profit = temp_profit;
                newSID = stp->getSID();
            }

        }

    }
    //cout << "\nSensing Task [" << newSID-1 << "] max_profit: " << max_profit << "\n" << endl;

    if(newSID == -1) {
        SID = -1;
        return;
    }

    if(accReward > 0) {
        nmp = 100.0 * max_profit / accReward;
    }
    else if(accReward == 0) {
        nmp = 100.0 * max_profit / max_reward;
    }

    //cout << "nmp: " << nmp << endl;

    if (nmp_thres > nmp) {
        SID = -1;
        return;
    }

    SID = newSID;
    (*sensingTaskList)[newSID-1].update(false, this);

}

void User::update(int cost, int distanceRemaing, int x_new, int y_new) {
    opTime   += 1;
    opCost   += cost;
    distance  = distanceRemaing;
    x         = x_new;
    y         = y_new;
}

void User::update(int newSID, float reward) {
    SID        = newSID;
    accReward += reward;

}

int User::getOpTime() {
    return opTime;
}

int User:: getOpCost() {
    return opCost;
}

float User::getAccReward() {
    return accReward;
}

User::~User() {

}
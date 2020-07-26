#include "SensingTask.hpp"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/*            Construction Phase:             */
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* Constructor */
SensingTask::SensingTask(int indexSID, float incentive) {
    /* All members are initialized */

    SID             = indexSID;
    UID             = 0;
    x               = -1;
    y               = -1;
    status          = false;
    finReward       = 0;
    reward          = 0;
    baseReward      = incentive;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/*                Game Phase:                 */
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* Reset method */
void SensingTask::set(int x_pos, int y_pos) {
    /* incoming x&y parameters represent random valid coordinates in the enviroment */

    x           = x_pos;
    y           = y_pos;
    status      = false;
    UID         = 0;
}

/* Attribute set method */
void SensingTask::update(bool statusChange, int newUID) {
    /* upon capture by a user the members of the ST must be updated */
    status      = statusChange;
    finReward   = reward;
    UID         = newUID;
}

void SensingTask::setReward(float incentive) {
    reward = incentive;
}

void SensingTask::setFinReward(float incentive) {
    finReward = incentive;
}

/* Attribute get method */
bool SensingTask::getStatus() {
    return status;
}

/* Attribute get method */
float SensingTask::getReward() {
    return reward;
}

float SensingTask::getFinReward() {
    return finReward;
}

float SensingTask::getBaseReward() {
    return baseReward;
}

/* destructor */
SensingTask::~SensingTask() {

}
#include "SensingTask.hpp"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/*            Construction Phase:             */
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* Constructor */
SensingTask::SensingTask(int indexSID, float incentive) {
    /* All members are initialized */

    SID         = indexSID;
    x           = -1;
    y           = -1;
    status      = false;
    reward      = incentive;
    participant = nullptr;
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
    participant = nullptr;
}

/* Attribute set method */
void SensingTask::update(bool statusChange, User *userParticipant) {
    /* upon capture by a user the members of the ST must be updated */
    status      = statusChange;
    participant = userParticipant;
}

/* Attribute get method */
bool SensingTask::getStatus() {
    return status;
}

/* Attribute get method */
float SensingTask::getReward() {
    return reward;
}

/* Attribute get method */
User* SensingTask::getUser() {
    return participant;
}

/* destructor */
SensingTask::~SensingTask() {

}
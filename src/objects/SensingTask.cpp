#include "SensingTask.hpp"

SensingTask::SensingTask(int indexSID, float incentive) {
    SID         = indexSID;
    x           = -1;
    y           = -1;
    status      = false;
    reward      = incentive;
    participant = nullptr;
}

void SensingTask::set(int x, int y) {
    x           = x;
    y           = y;
    status      = false;
    participant = nullptr;
}

void SensingTask::update(bool statusChange, User *userParticipant) {
    status = statusChange;
    participant = userParticipant;
}

bool SensingTask::getStatus() {
    return status;
}

float SensingTask::getReward() {
    return reward;
}

User* SensingTask::getUser() {
    return participant;
}

SensingTask::~SensingTask() {

}
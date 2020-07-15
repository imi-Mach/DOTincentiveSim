#include "Cell.hpp"

Cell::Cell() {
    resVec = new vector<User*>;
    cost = 1;                   /* default is 1 */
    sensingTask = nullptr;
}

void Cell::set(int geoCost){
    cost = geoCost;
    if (!resVec->empty()) {
        resVec->clear();
    }
}

void Cell::setTask(SensingTask* task) {
    sensingTask = task;
}

void Cell::addUser(User* newUser) {
    
    int size;
    int i;

    /* empty vector case */
    if(resVec->empty()) {
        resVec->push_back(newUser);
        return;
    }

    size = resVec->size();

    /* scan through vector for NULL pointers */
    for(i = 0; i < size; i++) {
        if((*resVec)[i] == nullptr) {
            (*resVec)[i] = newUser;
            return;
        }
    }

    /* vector is full, add another container */
    resVec->push_back(newUser);

}

void Cell::delUser(User* leavingUser) {
    int size = resVec->size();
    for(int i = 0; i < size; i++) {
        if((*resVec)[i] == leavingUser) {
            (*resVec)[i] = nullptr;
            return;
        }
    }
}

int Cell::getCost(){
    return cost;
}

SensingTask* Cell::getTask() {
    return sensingTask;
}

vector<User*>* Cell::getResVec() {
    return resVec;
}

Cell::~Cell() {
    resVec->clear();
    delete resVec;
}
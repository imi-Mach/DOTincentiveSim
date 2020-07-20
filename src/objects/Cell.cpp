#include "Cell.hpp"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/*            Construction Phase:             */
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* Constructor */
Cell::Cell() {
    /* All variables initialized */

    cost = 1;
    sensingTask = nullptr;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/*                Game Phase:                 */
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* Reset method */
void Cell::set(int geoCost){
    /* All variables are reset and recalculated*/

    /* geographical cost assigned during enviromental set() method */
    cost = geoCost;

    /* any traces of user occupants is reset */
    if (!resVec.empty()) {  
        resVec.clear();
    }
    sensingTask = nullptr;  /* sensingTask ptr is reset to nullptr */
}

/* Attribute set method */
void Cell::setTask(SensingTask* task) {
    sensingTask = task;
}

/* Attribute manipulator method */
void Cell::addUser(User* newUser) {
    /* Called when user is assigned/moving to/from a cell  */

    int size = 0;
    
    /* empty vector case */
    if(resVec.empty()) {
        resVec.push_back(newUser);
        return;
    }

    size = resVec.size();

    /* scan through vector for NULL pointers */
    for(int i = 0; i < size; i++) {
        if(resVec[i] == nullptr) {
            resVec[i] = newUser;
            return;
        }
    }

    /* vector is full, add another container */
    resVec.push_back(newUser);

}

/* Attribute manipulator method */
void Cell::delUser(User* leavingUser) {
    int size = resVec.size();
    for(int i = 0; i < size; i++) {
        if(resVec[i] == leavingUser) {
            resVec[i] = nullptr;
            return;
        }
    }
}

/* Attribute get method */
int Cell::getCost(){
    return cost;
}

/* Attribute get method */
SensingTask* Cell::getTask() {
    return sensingTask;
}

/* Attribute get method */
vector<User*>* Cell::getResVec() {
    return &resVec;
}

/* Destructor */
Cell::~Cell() {

}
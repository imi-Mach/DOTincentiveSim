#include "Entity.hpp"

void Entity::setCoord(const char component, int posVal) {
    switch(component) {
        case 'x':
            x = posVal;
            return;
            break;

        case 'y':
            y = posVal;
            return;
            break;
        
        default:

    }
    bail(2, "Incorrect use of setCoord function");
    cerr << "FATAL error: setCoord failed to return coord or error!" << endl;
    return;
}

int Entity::getCoord(const char component) {
    switch(component) {
        case 'x':
            return x;
            break;

        case 'y':
            return y;
            break;
        
        default:

    }
    bail(2, "FATAL error: getCoord failed to return coord or error!");
    return -2;
}

int Entity::getSID() {
    return SID;
}

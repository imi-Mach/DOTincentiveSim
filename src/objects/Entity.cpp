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

    }

    bail(2, "FATAL error: setCoord failed to return coord or error!");
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

    }
    
    bail(2, "FATAL error: getCoord failed to return coord or error!");
    return -2;
}

int Entity::getSID() {
    return SID;
}

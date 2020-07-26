#include "Entity.hpp"

/* Attribute set method */
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

/* Attribute get method */
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

/* Attribute get method */
int Entity::getSID() {
    return SID;
}

int Entity::getUID() {
    return UID;
}

#ifndef ENTITY
#define ENTITY

#include "functions.h"

class Entity {
    public:
        void setCoord(const char, int);
        int  getCoord(const char);
        int  getSID();
    protected:
        int SID;            /* set(): */
        int x;
        int y;

};

#endif
#ifndef ENTITY
#define ENTITY

#include "functions.h"  /* definition of bail function */

class Entity {          /* Entity is a base class for User and SensingTask */
    public:
        void setCoord(const char, int); /* func desc: IN: x or y component, value of x or y. OUT: n/a*/
        int  getCoord(const char);      /* func desc: IN: x or y component.                  OUT: value of x or y */
        int  getSID();                  /* func desc: IN: n/a.                               OUT: SID of entity */
        int  getUID();
    protected:
        int SID;                        /* var desc: sensing task I.D. */
        int UID;
        int x;                          /* var desc: x position. */
        int y;                          /* var desc: y position. */

};

#endif
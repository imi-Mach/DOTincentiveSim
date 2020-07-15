#ifndef ENVIRO
#define ENVIRO

#include <vector>
#include "Cell.hpp"
#include "functions.h"

enum boardType {
    UNIFORM,
    SIMPLE,
    COMPLEX,
    RANDOM
};

class Enviroment {
    public:
        Enviroment(int);                /* parameter desc: sideLength of square board */
        int assignCost(int, int);       /* parameter desc: assign geo cost based on x-y coords */
        int getAvgCost();
        void set();                     /* parameter desc:  */
        Cell* getCell(int, int);        /* parameter desc: x coord and y coord for entity placement */
        ~Enviroment();
    private:
        boardType geoSetting;
        int avgCost;
        int size;                         /* c): */
        vector< vector<Cell> >* grid;      /* c): 2d map of cells */

};

#endif
#ifndef ENVIRO
#define ENVIRO

#include <vector>      /* 2-d vector forms the grid cells */
#include "Cell.hpp"    /* definition of cell */
#include "functions.h" /* definiton of bail function*/

class Cell;

enum boardType {       /* types of enviroment cost patterns */
    UNIFORM,
    SIMPLE,
    COMPLEX,
    RANDOM
};

class Enviroment {      /* Enviroment maintains graph of cells */
    public:
        Enviroment(boardType, int);  /* func desc: IN: geographical setting of board, board size. OUT: initialized enviroment */
        int assignCost(int, int);    /* func desc: IN: x, and y position of cell.                 OUT: cost of entering cell */
        int getAvgCost();            /* func desc: IN: n/a.                                       OUT: average cost of travel cell-to-cell */
        void set();                  /* func desc: IN: n/a.                                       OUT: re-initialized cell */
        Cell* getCell(int, int);     /* func desc: IN: x, and y values of interest.               OUT: cell of interst */
        ~Enviroment();
    private:
        boardType geoSetting;        /* var desc: stores type of enviroment cost pattern */
        int avgCost;                 /* var desc: average cost of traveling on the board */
        int size;                    /* var desc: side length of square board */
        vector< vector<Cell> > grid; /* var desc: vector with celll vector members or grid of cells */

};

#endif
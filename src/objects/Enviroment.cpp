#include "Enviroment.hpp"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/*            Construction Phase:             */
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* Constructor */
Enviroment::Enviroment(boardType geoType, int gameSize) {
    /* construction depends on Game constructor */

    geoSetting = geoType;  /* type of board settings is determined in main.cpp */
    avgCost    = 0;
    size       = gameSize; /* size of board passed from main.cpp*/

    /* vector of cell is initialized and used to copy vector members in new grid  */
    vector<Cell> v;
    
    for(int i = 0; i < size; i++) {  /* first vector of cells is created */
        v.push_back(Cell());
        
    }
    
    for(int i = 0; i < size; i++) {  /* second vector of vectors is created */
        grid.push_back(v);
    }
    
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/*                Game Phase:                 */
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* Attribute manipulator method */
int Enviroment::assignCost(int x, int y) {
    /* cost patterns are determined by the boards settings */

    switch(geoSetting) {
        case UNIFORM:       /* only case programmed */
            return 1;
        case SIMPLE:        /* could be simple non-uniform costs */
            return 1;
        case COMPLEX:       /* could be square graph with missing nodes and unique costs */
            return 1;
        case RANDOM:        /* could be random costs */
            return 1;
    }

    bail(2, "FATAL error: Geo cost was not properly set");
    return 1;
}

/* Attribute get method */
int Enviroment::getAvgCost() {
    return avgCost;
}

/* Reset method */
void Enviroment::set() {
    /* each trial the avg cost and grid of sells are reset */

    int sumCostOfCells = 0;
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            grid[i][j].set(assignCost(i, j));
            sumCostOfCells += grid[i][j].getCost();
        }
    }
    avgCost = sumCostOfCells / (size * size);
}

/* Attribute get method */
Cell* Enviroment::getCell(int x, int y) {
    /* grid access with minor exception handling */

    Cell* cp = nullptr;

    try {
        cp = &grid[x][y];
    }
    catch (const std::out_of_range& oor) {
        cerr << "Out of Range error (getCell: size = " << size << ", x = " << x << ", y = " << y << "): " << oor.what() << endl;
        exit(2);
    }

    return cp;
}

/* Deconstructor */
Enviroment::~Enviroment() {
    
}
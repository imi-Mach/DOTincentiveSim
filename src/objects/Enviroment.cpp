#include "Enviroment.hpp"

Enviroment::Enviroment(int gameSize) { 
    geoSetting = UNIFORM;
    avgCost = 0;
    size = gameSize;

    vector<Cell> v;
    
    for(int i = 0; i < size; i++) {
        v.push_back(Cell());
        
    }
    
    for(int i = 0; i < size; i++) {
        grid.push_back(v);
    }

    /* DEBUG STAGE: 
    for(int i = 0; i < size; i++)  {
        vector<Cell> v;
        for(int j = 0; j < size; j++) {
                v.push_back(Cell());
        }
        grid.push_back(v);
    }
    */
    
}

int Enviroment::assignCost(int x, int y) {
    switch(geoSetting) {
        case UNIFORM:       /* only case programmed */
            return 1;
        case SIMPLE:
            return 1;
        case COMPLEX:
            return 1;
        case RANDOM:
            return 1;
    }

    bail(2, "FATAL error: Geo cost was not properly set");
    return 1;
}

int Enviroment::getAvgCost() {
    return avgCost;
}

void Enviroment::set() {
    int sumCostOfCells = 0;
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            grid[i][j].set(assignCost(i, j));
            sumCostOfCells += grid[i][j].getCost();
        }
    }
    avgCost = sumCostOfCells / (size * size);
}

Cell* Enviroment::getCell(int x, int y) {
    
    Cell* cp;

    try {
        cp = &grid[x][y];
    }
    catch (const std::out_of_range& oor) {
        cerr << "Out of Range error (getCell: size = " << size << ", x = " << x << ", y = " << y << "): " << oor.what() << endl;
        exit(2);
    }

    return cp;
}

Enviroment::~Enviroment() {
    /*
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            grid[i][j].~Cell();
        }
        grid[i].clear();
    }
    grid.clear();
    */
}
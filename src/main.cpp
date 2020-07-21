#include <iostream>
#include <cmath>
#include "fstream"
#include "Game.hpp"
#include "functions.h"

/* how many users do we need? */
/* assuming square board */
/* how do we know what percentage is eco feasible? */

using namespace std;

int main(int argc, char **argv) {
    
    #ifdef DEBUG
    cout << string(50, '\n') << endl;
    #endif
    
    ofstream dataFile;
    int   round        = 1;
    int   trials       = 0;
    int   numIncent    = 0;
    int   userNum      = 0;
    int   boardSize    = 0;
    float preBudget    = 0.0;  /* optimize problem with numIncentives */
    float percent      = 0.0;
    bool verboseOption = false;
    boardType geoType  = UNIFORM;



    parseArgs(argc, argv, &trials, &userNum, &boardSize, &preBudget, &percent, &verboseOption);
    
    dataFile.open("data.txt", ios_base::app);

    if(!dataFile.is_open()) {
        bail(99, "Failed to open data file.");
    }
    
    numIncent = (int)floor(((float)(boardSize * boardSize) * percent / 100));
    
    Enviroment board(geoType, boardSize);
    Game game(&board, numIncent, userNum, boardSize, preBudget, verboseOption);    /* constructing phase */
    
    if(verboseOption) {
        dataFile << "Number of Trials:\t" << trials
                << "\nBoard Size: \t\t" << boardSize << "x" << boardSize
                << "\nPredicted budget:\t" << preBudget
                << "\nPercentage: \t\t" << percent
                << "\nNumber of Users:\t" << userNum
                << "\nNumber of tasks:\t" << numIncent
                << endl;
    }
    
    while(trials >= round) {
        game.set(round);            /* set non-static variables to start */
        game.play();                /* turn based game, ends when users all dropout */
        game.save(&dataFile);       /* print results into a file the results */
        round++;
    }

    game.summary(&dataFile);

    dataFile.close();

    return 0;
}

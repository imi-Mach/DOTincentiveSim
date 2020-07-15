#include <iostream>
#include <cmath>
#include "elements.hpp"
#include "functions.hpp"

/* 
 * To-Do's:
 *  - finish deconstructors (mem deletes)
 *  - fix make file to compile elements.cpp and link to main
 *  - debug (many bugs, mem loss, frees ...)
 *
 */

/* how many users do we need? */
/* assuming square board */
/* how do we know what percentage is eco feasible? */

using namespace std;

int main(int argc, char **argv) {
    
    cout << string(50, '\n') << endl;

    ofstream dataFile;
    int   trials;
    int   numIncent;
    int   userNum;
    int   boardSize;
    float preBudget;  /* optimize problem with numIncentives */
    float percent;

    dataFile.open("data.txt");

    int   round = 1;

    parseArgs(argc, argv, &trials, &userNum, &boardSize, &preBudget, &percent);
    
    numIncent = (int)floor(((float)(boardSize * boardSize) * percent / 100));
    
    Game game(numIncent, userNum, boardSize, preBudget);    /* constructing phase */

    dataFile << "Number of Trials:\t" << trials
             << "\nBoard Size: \t\t" << boardSize << "x" << boardSize
             << "\nPredicted budget:\t" << preBudget
             << "\nPercentage: \t\t" << percent
             << "\nNumber of Users:\t" << userNum
             << "\nNumber of tasks:\t" << numIncent
             << '\n';

    while(trials >= round) {
        game.set(round);            /* set non-static variables to start */
        game.play();           /* turn based game, ends when users all dropout */
        game.save(&dataFile);           /* print results into a file the results */
        round++;
    }
    
    dataFile.close();

    return 0;
}

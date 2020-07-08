#include <iostream>
#include "elements.hpp"
#include "functions.hpp"

/* how many users do we need? */
/* assuming square board */
/* how do we know what percentage is eco feasible? */

using namespace std;

int main(int argc, char **argv) {
    
    cout << string(50, '\n') << endl;

    int   numIncent;
    int   trials;
    int   userNum;
    int   boardSize;
    float preBudget;  /* optimize problem with numIncentives */
    float percent;

    int   round = 1;


    parseArgs(argc, argv, &trials, &userNum, &boardSize, &preBudget, &percent);
    
    numIncent = (int)((float)boardSize * percent / 100);
    
    enviroment board(numIncent, preBudget, userNum, boardSize, percent);    /* constructing phase */

    while(trials >= round) {
        board.set();            /* set non-static variables to start */
        board.play();           /* turn based game, ends when users all dropout */
        board.save();           /* print results into a file the results */
        round++;
    }
    
    return 0;
}

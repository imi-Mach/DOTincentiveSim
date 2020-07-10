#include <iostream>
#include <cmath>
#include "elements.hpp"
#include "functions.hpp"

/* how many users do we need? */
/* assuming square board */
/* how do we know what percentage is eco feasible? */

using namespace std;

int main(int argc, char **argv) {
    
    cout << string(50, '\n') << endl;

    int   trials;
    int   numIncent;
    int   userNum;
    int   boardSize;
    float preBudget;  /* optimize problem with numIncentives */
    float percent;

    int   round = 1;

    parseArgs(argc, argv, &trials, &userNum, &boardSize, &preBudget, &percent);
    
    numIncent = (int)floor(((float)(boardSize * boardSize) * percent / 100));
    
    Game game(numIncent, userNum, boardSize, preBudget);    /* constructing phase */

    while(trials >= round) {
        game.set();            /* set non-static variables to start */
        game.play();           /* turn based game, ends when users all dropout */
        game.save();           /* print results into a file the results */
        round++;
    }
    
    return 0;
}

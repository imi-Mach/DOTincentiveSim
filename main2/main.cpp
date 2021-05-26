#include <iostream>
#include <Game.hpp>
#include <string>
#include <cstring>
#include <vector>

using namespace std;

int main(int argc, char **argv) {
    ofstream dataFile;
    int    round         = 1; /* constant */
    int    trials        = 10; /* May want to change: */
    int    numIncent     = 0;
    int    userNum       = 15;
    int    boardSize     = 10;
    float  x_spacing     = 0.6; /* May want to change: 0.6 */
    float  y_spacing     = 10;  /* May want to change: 10 */
    float  x_offset      = 20;  /* coverage percentage */
    float  y_offset      = 100; /* predicted budget */
    float  percent       = 0;   /* constant */
    float  preBudget     = 0;   /* constant */
    size_t dataPoints    = 100; /* 100 */
    boardType geoType    = UNIFORM;
    IM_t incentiveMechanism = D_STCENTER_CLUSTER; /* Where you can change the IM */
    int counter             = 0;

    dataFile.open("DSTCC_DataFile.txt", ios_base::app);

    if(!dataFile.is_open()) {
        bail(99, "Failed to open data file.");
    }

    for (size_t x = 0; x < dataPoints; x++) {

        for (size_t y = 0; y < dataPoints; y++) {
            percent = (x_spacing * (float) x) + x_offset;
            preBudget = (y_spacing * (float) y) + y_offset;
            numIncent = (int)floor(((float)(boardSize * boardSize) * percent / 100));
            Enviroment board(geoType, boardSize);
            Game game(&board, incentiveMechanism, numIncent, userNum, boardSize, preBudget, false);

            while(trials >= round) {
                game.set(round);            /* set non-static variables to start */
                game.play();                /* turn based game, ends when users all dropout */
                game.save(&dataFile);       /* print results into a file the results */
                round++;
            }
            round = 1;
            dataFile << x << " " << y << " " << percent << " " << preBudget << " ";
            game.summary(&dataFile);
            counter++;
        }
        cout << counter << "/" << dataPoints * dataPoints << endl;
    }

    dataFile.close();

    return 0;

}
#include <iostream>
#include <Game.hpp>
#include <string>
#include <cstring>
#include <vector>

using namespace std;

int main(int argc, char **argv) {
    ofstream dataFile;
    int    round         = 1;
    int    trials        = 25;
    int    numIncent     = 0;
    int    userNum       = 3;
    int    boardSize     = 10;
    float  x_spacing     = 0.3;
    float  y_spacing     = 5;
    float  x_offset      = 20;
    float  y_offset      = 100;
    float  percent       = 0;
    float  preBudget     = 0;
    size_t dataPoints    = 200; /* 100 */
    boardType geoType    = UNIFORM;
    IM_t incentiveMechanism = S_UNIFORM;
    int counter          = 0;

    dataFile.open("data2.txt", ios_base::app);

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
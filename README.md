# DOTincentiveSim (VERSION: 2.0)
This is the C++ code for simulating different IM.

## Instructions:

NEW Instructions

(Running several rounds)

1. go to ./main2 folder
2. open main.cpp
3. Adjust the settings as desired
    A. You can view the IM options in "./src/objects/Game.hpp"
    B. Make sure to change the name of teh output file (Line 27 in main.cpp)
4. To run the test:
    A. type "make clean"
    B. type "make test"
    C. "./test" or "./test.out"


### 1. Compile with C++11 std or higher.
- If you are on linux this may not work, unless the default compiler is changed to g++ (currently clang++)

### 2. a) For singular simmulation settings, type "make" in terminal to produce "./sim1".
- Assuming libraries are properly setup (including standards), there should be no errors.

### 2. b) For data point collection with varrying settings in simmulation use "make test" to produce "./test.out".
- Depending on the configuration in "./main2/main.cpp", predicted budget and coverage will be changed for each data point.

### 3. Depending on executable settings "data.txt" will have the results.
- Consider verbose option if you would like to see what the simmulations look like.

## Note:
- There are 8+ IM that must be manually edited to choose from
- For board size 10 and number of users 3, the simmulation can run 1,000,000 trials in about 1 min max depending on level of coverage.
- If the executable was successful than the data on the results should be in "data.txt"
- If the process is hung, then send "ctrl + c" signal to exit.

## To-do:
- Add IM command line options.
- Add IM that approximate the theoretical result.

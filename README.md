# DOTincentiveSim (VERSION: 1.9)
This is the C++ code for simulating different IM.

## Instructions:

### 1. Compile with C++11 std or higher.
- If you are on linux this may not work, unless the default compiler is changed to g++ (currently clang++)

### 2. a) For singular simmulation settings, type "make" in terminal to produce "./sim1".
- Assuming libraries are properly setup (including standards), there should be no errors.

### 2. b) For data point collection with varrying settings in simmulation use "make test" to produce "./test.out".
- Depending on the configuration in "./main2/main.cpp", predicted budget and coverage will be changed for each data point.

### 3. Depending on executable settings "data.txt" will have the results.
- Consider verbose option if you would like to see what the simmulations look like.

## Note:
- For board size 10 and number of users 3, the simmulation can run 1,000,000 trials in about 1 min max depending on level of coverage.
- If the executable was successful than the data on the results should be in "data.txt"
- If the process is hung, then send "ctrl + c" signal to exit.

## To-do:
- Implement different incentive mechanisms. (+1 static, +2 dynamic)

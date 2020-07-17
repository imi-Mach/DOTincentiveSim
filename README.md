# DOTincentiveSim
This is the C++ code for simulating different IM.

## Instructions:

1. Compile with C++11 std or higher.
- If you are on linux this may not work, unless the default compiler is changed to g++ (currently clang++)

2. Type make in terminal.
- Assuming libraries are properly setup (including standards), there should be no errors.

3. Enter "./sim1" with correct arguments.
- They should be in the help message if you enter anything else.

## Note:
- The game is relativly stable for ~10 trials (-t 10) on board size 10x10 (-b 10).

To-do:
- Fix memory management issues (Working on trial == 1 case to higher with 0 memleak)

#include "functions.hpp"

using namespace std;

void parseArgs(int argc, char **argv, int *trials, int *userNum, int *boardSize, float *preBudget, float *percent) {

    if (argc == 11) {
        if ((strcmp(argv[3], "-b") || strcmp(argv[3], "--board")) && isNumber(argv[4])) {
            *boardSize = atoi(argv[4]);
            if(*userNum < 0) help();
        }
        else {
            help();
        }

        if ((strcmp(argv[1], "-u") || strcmp(argv[1], "--user")) && isNumber(argv[2])) {
            *userNum = atoi(argv[2]);
            if (*userNum > *boardSize) help();
        }
        else {
            help();
        }

        if ((strcmp(argv[5], "-p") || strcmp(argv[5], "--percent")) && isFloat(argv[6])) {
            *percent = stof(argv[6]);
            if (*percent > 100 || *percent < 0) help();
        }
        else {
            help();
        }

        if ((strcmp(argv[7], "-pb") || strcmp(argv[7], "--prebudget")) && isFloat(argv[8])) {
            *preBudget = stof(argv[8]);
            if (*percent < 0) help();
        }
        else {
            help();
        }

        if ((strcmp(argv[9], "-t") || strcmp(argv[9], "--trials")) && isNumber(argv[10])) {
            *trials = atoi(argv[10]);
            if (*trials < 0) help();
        }
        else {
            help();
        }

    }
    else {
        help();
    }

}

bool isNumber(string s){
    string::const_iterator it = s.begin();
    while (it != s.end() && isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

bool isFloat(string myString) {
    istringstream iss(myString);
    float f;
    iss >> noskipws >> f;
    return iss.eof() && !iss.fail();
    
}

void help(void) {
    cout << "\n---Parameters for program---\n" << endl;;
    cout << "\"./sim1 -u|--users <# of users> -b|--boardsize <dimension of square board> -p|--percent <percentage of coverage> -pb|--prebudget <budget with decimals> -t|--trials <# of trials>\"\n" << endl;
    cout << "Users:\t\tmust be smaller than board and a non-negative integer." << endl;
    cout << "Boardsize:\tmust be a non-negative integer." << endl;
    cout << "Percent:\tmust be a decimal number in range of [0.0,100.0]" << endl;
    cout << "Prebudget:\tmust be a non-negative decimal." << endl;
    cout << "Trials:\t\tmust be a postive integer.\n" << endl;
    cout << "(If this message appears it might be because format is incorrect)" << endl;
    exit(0);
}

void bail(int rc , string msg){
    cout << '(' << rc << ") - " << msg << endl;
    exit(rc);
}



#ifndef FUNCTIONS
#define FUNCTIONS

#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>

using namespace std;

void parseArgs(int, char **, int *, int *, int *, float *, float *);
bool isNumber(string);
bool isFloat(string);
void help(void);
void bail(int, string);
#endif

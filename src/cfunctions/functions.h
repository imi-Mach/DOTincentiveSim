#ifndef FUNCTIONS
#define FUNCTIONS

#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <string.h>


using namespace std;

void parseArgs(int, char **, int *, int *, int *, float *, float *);
bool isNumber(string);
bool isFloat(string);
int  rng(int);
void help(void);
void bail(int, string);
#endif

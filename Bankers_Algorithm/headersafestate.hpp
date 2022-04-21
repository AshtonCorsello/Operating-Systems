#ifndef BANKERS_ALGO
#define BANKERS_ALGO

#include <iostream>
#include <cstdlib>
#include <fstream>

const int n = 5; //Num of processes
const int m = 3; //Num of resource types

struct System {
        int Allocation[n][m];
        int Max[n][m];
        int Available[m];
        int Need[n][m];
};

#endif        

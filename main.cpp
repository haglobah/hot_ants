#include <vector>
#include <iostream>
#include "simulation.h"

int main(){
    
    Simulation sim = Simulation();
    
    printMatrix(sim._heat_matrix);

    return 0;
}
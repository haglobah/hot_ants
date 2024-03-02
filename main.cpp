#include <vector>
#include <iostream>
#include "simulation.h"


void walk(matrix heatmap, std::vector<Ant> Ants){
    for (int i = 0; i < Ants.size(); i++){
        //calculate change in position
        double dx = cos(Ants[i]._direction)*Ants[i]._speed;
        double dy = sin(Ants[i]._direction)*Ants[i]._speed;
        //change current position using dx, dy
        Ants[i]._current_position = {Ants[i]._current_position.first + dx, Ants[i]._current_position.second + dy};
        //update path with new ent
    } 
}


void death(Simulation& sim){
    std::vector<Ant> ants = sim._ants;
    for (Ant ant : sim._ants){
        //if (ant._current_position.second)
    };
}


int main(){
    
    Simulation sim = Simulation();

    while (true) {
        break ;
    };
    
    printMatrix(sim._heat_matrix);

    

    return 0;
}
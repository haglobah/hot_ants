#include <vector>
#include <iostream>
#include "simulation.h"


void walk(Simulation& sim){
    std::vector<Ant> ants = sim._ants;
    for (int i = 0; i < ants.size(); i++){
        //calculate change in position
        double dx = cos(ants[i]._direction)*ants[i]._speed;
        double dy = sin(ants[i]._direction)*ants[i]._speed;
        //change current position using dx, dy
        ants[i]._current_position = {ants[i]._current_position.first + dx, ants[i]._current_position.second + dy};
        //update path with new ent
        ants[i]._path.push_back(ants[i]._current_position)
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
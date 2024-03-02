#include <vector>
#include <iostream>
#include "simulation.h"


void collect(Simulation& sim)
{

}

void orientate(Simulation& sim)
{

}

void walk(Simulation& sim)
{
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


void execute_death(Simulation& sim){
    for (Ant ant : sim._ants){
        if (ant._current_position.second == (Y_DIM-1)){
            //update pheromones map
            for (std::pair<int,int> pos : ant._path){
                int x = pos.first;
                int y = pos.second;

                sim._phero_matrix[x][y];
            };
        };
    };
}

void upate_heatmap(Simulation& sim, matrix heatsource_map)
{

}

void diffuse_pheromones(Simulation& sim)
{

}

int main(){
    
    Simulation sim = Simulation();

    while (true) {
        collect(sim);
        orientate(sim);
        walk(sim);
        execute_death(sim);
        upate_heatmap(sim, heatsource_map);
        diffuse_pheromones(sim);
    }
    
    printMatrix(sim._heat_matrix);

    

    return 0;
}
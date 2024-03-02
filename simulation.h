#pragma once
#include "ant.h"
#include "utils.h"
#include <random>
#include <vector>

class Simulation {
    matrix generate_heat_map(){
        //should make matrix with high values in the middle (sin on x,y axis)
        matrix result = initial_heat;
        for (unsigned int i = 0; i < X_DIM; ++i){
            for (unsigned int j = 0; j < Y_DIM; ++j){
            result[i][j] = 5*sin(i*M_PI/X_DIM)+sin(j*M_PI/Y_DIM);
            };
        };
        return result;
    }

    matrix generate_phero_map(){
        matrix result = initial_pheromones;
    }

    public:

        Simulation(){
            _heat_matrix = generate_heat_map();
            _phero_matrix = generate_phero_map();
        }
        int _max_time_steps;
        matrix _heat_matrix;
        matrix _phero_matrix;
        std::vector<Ant> _ants;

};


#include "ant.h"
#include "utils.h"
#pragma once
#include <random>

class Simulation {
    matrix generate_heat_map(){
        //should make matrix with high values in the middle (sin on x,y axis)
        matrix result = initial_heat;
        for (unsigned int i = 0; i < X_DIM; ++i){
            for (unsigned int j = 0; j < Y_DIM; ++j){
            result[i][j] = sin(i*M_PI/X_DIM)+sin(j*M_PI/Y_DIM);
            };
        };
        return result;
    }
    matrix generate_heat_map_2(){
        // should make a matrix with squares of different heat
        matrix result = initial_heat;
        unsigned int num_sq_x = 10;
        unsigned int num_sq_y = 3;
        unsigned int squares_x = X_DIM/num_sq_x;
        unsigned int squares_y = Y_DIM/3;
        double val_x = 0.0;
        double val_y = 0.0;
        for (unsigned int k = 0; k < num_sq_x; ++k){
            for (unsigned int s = 0; s < num_sq_y; ++s){
                for (unsigned int i = k; i < k+squares_x; ++i){
                    for (unsigned int j = s; j < k+squares_y; ++j){
                        if(k%2 == 0){
                            val_x = 1;
                        };
                        if(s%2 == 0){
                            val_y = 1;
                        };
                        result[i][j] = val_x + val_y;
                    };
                };
            };
        };
        return result;
    }

    public:

        Simulation(){
            _heat_matrix = generate_heat_map();
        }
        double _ant_heat_capacity;
        int _max_time_steps;
        matrix _heat_matrix;

};


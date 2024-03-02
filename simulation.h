#pragma once
#include "ant.h"
#include "utils.h"
#include <random>
#include <vector>
#include <fstream>
#include <iostream>

class Simulation {
    matrix generate_heat_map(){
        //should make matrix with high values in the middle (sin on x,y axis)
        matrix result = initial_heat;
        for (unsigned int i = 0; i < X_DIM; ++i){
            for (unsigned int j = 0; j < Y_DIM; ++j){
            result[i][j] = 5*sin(i*M_PI/X_DIM)+sin(j*M_PI/Y_DIM);
            }
        }
        return result;
    }

    matrix generate_heatsource_map() {
        return initial_heatsource;
    }

    matrix generate_phero_map(){
        return initial_pheromones;
    }

    public:

        void saveSimState(std::ofstream& heatFile, std::ofstream& pheroFile){
            //printMatrix(_heat_matrix, false);
            //printMatrix(_phero_matrix, false);
            for(int i = 0; i < X_DIM; ++i) {
                for(int j = 0; j < Y_DIM; ++j) {
                    if (j == 0) {
                        heatFile << _heat_matrix.at(i).at(j);
                    } else {
                        heatFile << ", " << _heat_matrix.at(i).at(j);
                    }
                }
                heatFile << "\n";
            }
            for(int i = 0; i < X_DIM; ++i) {
                for(int j = 0; j < Y_DIM; ++j) {
                    if (j == 0) {
                        pheroFile << _phero_matrix.at(i).at(j);
                    } else {
                        pheroFile << ", " << _phero_matrix.at(i).at(j);
                    }
                }
                pheroFile << "\n";
            }
        }

        Simulation(int max_time_steps, int n_ants){
            _max_time_steps = max_time_steps;
            _heat_matrix = generate_heat_map();
            _heatsource_matrix = generate_heatsource_map();
            _phero_matrix = generate_phero_map();
            for(int i = 0; i < n_ants; i++) {
                _ants.push_back(Ant());
            }
            // Initialize Output files
            std::ofstream heatFile("heatHistory.txt");
            std::ofstream pheroFile("pheroHistory.txt");

            if(heatFile.is_open()){
                heatFile << max_time_steps << ", " << X_DIM << ", " << Y_DIM << "\n";
            }
            if(pheroFile.is_open()){
                pheroFile << max_time_steps << ", " << X_DIM << ", " << Y_DIM << "\n";
            }            
        }
        int _max_time_steps;
        matrix _heat_matrix;
        matrix _heatsource_matrix;
        matrix _phero_matrix;
        std::vector<Ant> _ants;
};


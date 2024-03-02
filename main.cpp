#include <vector>
#include <iostream>
#include "simulation.h"
#include <cmath>
#include <random>


void collect(Simulation& sim)
{
    int x;
    int y;
    double K = 1.0; //we'll maybe have to tweek that
    for (Ant ant : sim._ants){
        x = ant._current_position.x;
        y = ant._current_position.y;
        if (ant._ant_temperature < sim._heat_matrix.at(x).at(y)) {
            double t = ((sim._heat_matrix.at(x).at(y)-ant._ant_temperature)/sim._heat_matrix.at(x).at(y)) * K;
            ant._ant_temperature += t;
            sim._heat_matrix.at(x).at(y) -= t;
        }
    }
}

double sineSum(double x) {//used for orientate someday maybe??
            return sin(x) + sin(2 * x) + sin(3 * x); // Sum of 3 sine functions
        }

void orientate(Simulation& sim)
{
    for(Ant ant : sim._ants){
        ant._direction = 0;
        //return;
        
        // Create a random number engine
        std::random_device rd;
        std::mt19937 gen(rd());

        // Create a uniform real distribution between -0.5 and 0.5
        std::uniform_real_distribution<> dis(-0.5, 0.5);

        // Generate a random value in the range [0, 1)
        ant._direction = dis(gen);
        
    }
}
void print_ants(std::vector<Ant>& ants){
    std::vector<std::vector<char>> ants_matrix(Y_DIM, std::vector<char>(X_DIM, '.'));
    for(Ant ant : ants) {
        ants_matrix.at(ant._current_position.y).at(ant._current_position.x) = 'X';
    }
    printMatrix(ants_matrix, false);
}

void walk(Simulation& sim)
{   
    /*
    double bias_up = 1;
    double bias_down = 1;
    double bias_right = 2;
    for(Ant ant : sim._ants){
        int x = ant._current_position.x;
        int y = ant._current_position.y;
        if(x < X_DIM){
            double up = sim._heat_matrix.at(x+1).at(y) + sim._phero_matrix.at(x+1).at(y) + bias_up;
        } else { 
            double up = 0.0; 
        }
       
        double down =
    }
    */

    //std::vector<Ant> ants = sim._ants;
    //for (int i = 0; i < ants.size(); i++){
    //    //calculate change in position
    //    double dx = cos(ants[i]._direction)*ants[i]._speed;
    //    double dy = sin(ants[i]._direction)*ants[i]._speed;
    //    //change current position using dx, dy
    //    int destination_x = int(double(ants[i]._current_position.x) + dx);
    //    int destination_y = int(double(ants[i]._current_position.y) + dy);
    //    if(destination_x >= X_DIM || destination_x <= 0){
    //        ants[i]._direction *= -1;
    //        double dx = cos(ants[i]._direction)*ants[i]._speed;
    //        double dy = cos(ants[i]._direction)*ants[i]._speed;
    //        int destination_x = int(double(ants[i]._current_position.x) + dx);
    //    }
    //    if(destination_y >= Y_DIM || destination_y <= 0){
    //        ants[i]._direction += M_PI;
    //        double dx = cos(ants[i]._direction)*ants[i]._speed;
    //        double dy = cos(ants[i]._direction)*ants[i]._speed;
    //        int destination_y = int(double(ants[i]._current_position.x) + dx);
    //    }
    //    ants[i]._current_position = {destination_x, destination_y};
    //    //update path with new ent
    //    ants[i]._path.push_back(ants[i]._current_position);
    //} 
}


void execute_death(Simulation& sim)
{
    for (Ant ant : sim._ants){
        if (ant._current_position.y == (Y_DIM-1)){
            std::cout << "Ant died";
            //update pheromones map
            for (Point pos : ant._path){
                int x = pos.x;
                int y = pos.y;

                sim._phero_matrix.at(x).at(y) += ant._ant_temperature;
            };
            //reset ant path and position
            ant.reset_path();
            ant.reset_pos();
        };
    };
}

void upate_heatmap(Simulation& sim)
{
    for (unsigned int i = 0; i < X_DIM; ++i) {
        for (unsigned int j = 0; j < Y_DIM; ++j) {
            sim._heat_matrix[i][j] += sim._heatsource_matrix[i][j];
        }
    }
}

void diffuse_pheromones(Simulation& sim)
{
    for (unsigned int i = 0; i < X_DIM; ++i) {
        for (unsigned int j = 0; j < Y_DIM; ++j) {
            float diffused = sim._phero_matrix[i][j] - DIFFUSION;
            if (diffused < 0) {
                sim._phero_matrix[i][j] = 0;
            }
            else {
                sim._phero_matrix[i][j] = diffused;
            }
        }
    }
}

int main(){
    

    int max_time_steps = 1000;
    
    std::ofstream heatFile("heatHistory.txt");
    std::ofstream pheroFile("pheroHistory.txt");

    if(heatFile.is_open()){
        heatFile << max_time_steps << ", " << X_DIM << ", " << Y_DIM << "\n";
    }
    if(pheroFile.is_open()){
        pheroFile << max_time_steps << ", " << X_DIM << ", " << Y_DIM << "\n";
    }        
    
    Simulation sim(max_time_steps, 5);
    
    printMatrix(sim._heat_matrix, false);

    for (int i = 0; i < max_time_steps; ++i) {
        //print_ants(sim._ants);
        collect(sim);
        orientate(sim);
        walk(sim);
        execute_death(sim);
        upate_heatmap(sim);
        diffuse_pheromones(sim);
        sim.saveSimState(heatFile, pheroFile);
    }
    
    printMatrix(sim._heat_matrix, false);

    return 0;
}
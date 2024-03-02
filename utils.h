#pragma once

#include <vector>
#include <random>
#include <utility>

#define X_DIM 60
#define Y_DIM 120

#define X_SOURCE 0
#define Y_SOURCE 5

#define DIFFUSION 0.002


using matrix = std::vector<std::vector<double>>;
using position = std::pair<int,int>;

matrix initial_pheromones(X_DIM, std::vector<double>(Y_DIM, 0.0));
matrix initial_heat(X_DIM, std::vector<double>(Y_DIM, 0.0));
matrix initial_heatsource(X_DIM, std::vector<double>(Y_DIM, 1.0));

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> distrib_int(0, Y_DIM-1);
std::uniform_real_distribution<> distrib_real(0.0001, 1);

int y_random(){
    return distrib_int(gen);
}
double urand(){
    return distrib_real(gen);
}

template <typename T>
void printMatrix(const std::vector<std::vector<T>>& mat, bool csv) {
    for (const auto& row : mat) {
        for (T elem : row) {
            std::cout << elem << " ";
        }
        std::cout << std::endl; // Move to the next line after printing a row
    }
    std::cout << std::endl;
}

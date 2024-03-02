#pragma once

#include <vector>
#include <random>
#include <utility>

#define X_DIM 20
#define Y_DIM 10

#define X_SOURCE 0
#define Y_SOURCE 5

#define DIFFUSION 0.1


using matrix = std::vector<std::vector<double>>;
using position = std::pair<int,int>;

matrix initial_pheromones(X_DIM, std::vector<double>(Y_DIM, 0.0));
matrix initial_heat(X_DIM, std::vector<double>(Y_DIM, 0.0));
matrix initial_heatsource(X_DIM, std::vector<double>(Y_DIM, 1.0));

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> distrib(0, Y_DIM-1);
int y_random(){
    std::mt19937 gen(rd());
    return distrib(gen);
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

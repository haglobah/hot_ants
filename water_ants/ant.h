#include <vector>
#include <iostream>
#include <utility>
#include <random>
#include "utils.h"

struct Ant{
    std::pair<int,int> _current_position;
    std::pair<double, double> _velocity;
    std::vector<std::pair<int,int>> _path;
    double total_score;

    Ant(){
        _current_position = {0, y_random()};
    }


};
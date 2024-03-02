#pragma once
#include <vector>
#include <iostream>
#include <utility>
#include <random>
#include "utils.h"

struct Ant{
    std::pair<int,int> _current_position;
    double _direction; //angle in radian, for zero zeigt in positive x direction
    std::vector<std::pair<int,int>> _path;
    double _ant_heat_capacity;
    const double _speed = 2;

    Ant(){
        _current_position = {0, y_random()};
    }


};
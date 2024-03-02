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
    double _ant_temperature;
    const double _speed = 2;

    Ant(position current_position, double direction, double ant_temperature) : 
        _current_position(current_position),
        _direction(direction),
        _ant_temperature(ant_temperature)

    {}
    Ant() :
        _direction(0),
        _ant_temperature(0)
    {
        position random_start = {0, y_random()};
        _current_position = random_start;
        _path.push_back(random_start);
    }
};
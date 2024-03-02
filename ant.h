#pragma once
#include <vector>
#include <iostream>
#include <utility>
#include <random>
#include "utils.h"

struct Point {
    int x;
    int y;
};

struct Ant{
    Point _current_position;
    double _direction; //angle in radian, for zero zeigt in positive x direction
    std::vector<Point> _path;
    double _ant_temperature;
    const double _speed = 2;

    Ant(Point current_position, double direction, double ant_temperature) : 
        _current_position(current_position),
        _direction(direction),
        _ant_temperature(ant_temperature)

    {}
    Ant() :
        _direction(0),
        _ant_temperature(0)
    {
        Point random_start = {0, y_random()};
        _current_position = random_start;
        _path.push_back(random_start);
    }

    void reset_path() {
        for(unsigned int i = 0; i < _path.size(); i++){
            _path[i].x = 0;
            _path[i].y = 0;
        }
    }

    void reset_pos(){
        _current_position.x = 0;
        _direction = 0.0;
    }
};
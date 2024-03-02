cmake_minimum_required(VERSION 3.15)

project(water_ants)

set(CMAKE_CXX_STANDARD 20)

set(SOURCES
    main.cpp
    ant.h
    utils.h
    simulation.h
    )

add_executable(water_ants ${SOURCES})

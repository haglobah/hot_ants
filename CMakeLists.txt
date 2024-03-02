cmake_minimum_required(VERSION 3.15)

project(water_ants)

set(CMAKE_CXX_STANDARD 20)

set(SOURCES
    main.cpp
    ant.h
    utils.h
    simulation.h
    )

# Add optimization flags to the target

add_executable(water_ants ${SOURCES})

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    target_compile_options(water_ants PRIVATE -O3)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(time_series PRIVATE /O2)
endif()

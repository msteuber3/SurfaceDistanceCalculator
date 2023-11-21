cmake_minimum_required(VERSION 3.26)
project(SurfaceDistanceCalculator)

set(CMAKE_CXX_STANDARD 17)

add_executable(SurfaceDistanceCalculator
        src/main.cpp
        src/utils/userInput.cpp
        src/utils/writeFile.cpp
        src/utils/writeFile.h
        src/distanceCalc.cpp
        src/distanceCalc.h)

cmake_minimum_required(VERSION 3.16)
project(RubiksCubeSolver)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(rubiks_solver
        main.cpp
        Model/RubiksCube.cpp
        PatternDatabase/math.cpp
        PatternDatabase/NibbleArray.cpp
        PatternDatabase/PatternDatabase.cpp
        PatternDatabase/CornerPatternDatabase.cpp
        PatternDatabase/CornerDBMaker.cpp)

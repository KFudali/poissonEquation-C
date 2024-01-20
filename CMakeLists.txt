cmake_minimum_required(VERSION 3.8)

project(poissonEquation)

add_executable(poissonEquation src/poissonEquation.cpp)
target_include_directories(poissonEquation  PUBLIC include)
set_target_properties(poissonEquation PROPERTIES
    CXX_STANDARD 17
)
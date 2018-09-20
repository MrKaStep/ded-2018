cmake_minimum_required(VERSION 3.10)
project(sq_solver)

set(CMAKE_CXX_STANDARD 17)

add_library(sq_solver square_equation_solver.cpp)
include_directories(../util)
include_directories(../test)
target_link_libraries(sq_solver util)

add_executable(sq_solver_main main.cpp)
add_dependencies(sq_solver_main sq_solver)

add_executable(sq_solver_ut sq_solver_ut.cpp)
add_dependencies(sq_solver_ut sq_solver)
target_link_libraries(sq_solver_ut sq_solver my_test)
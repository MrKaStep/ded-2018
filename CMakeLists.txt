cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -O3")

project(ded-2018)

add_subdirectory(test)
add_subdirectory(util)
add_subdirectory(sq-solver)
add_subdirectory(oneginator)

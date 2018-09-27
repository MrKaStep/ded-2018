cmake_minimum_required(VERSION 3.10)

add_library(text text.cpp)

add_executable(oneginator_main main.cpp)
include_directories(../util)
target_link_libraries(oneginator_main text)
target_link_libraries(oneginator_main util)
cmake_minimum_required(VERSION 3.10)

add_library(my_test my_test.cpp ../oneginator/main.cpp ../oneginator/text.cpp ../oneginator/text.h)

include_directories(../util)
target_link_libraries(my_test util)
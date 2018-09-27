cmake_minimum_required(VERSION 3.10)

set(sources
        util.cpp
        util.h
        file.cpp
        file.h
        containers.h)

add_library(util ${sources})
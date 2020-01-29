cmake_minimum_required(VERSION 3.4.1)

add_library(
        delaunator-lib-static
        STATIC
        delaunator.cpp)

find_library(
        log-lib
        log)



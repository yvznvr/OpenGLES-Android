cmake_minimum_required(VERSION 3.4.1)

add_library(
        delaunator-lib
        SHARED
        delaunator-lib.cpp
        delaunator.h
        #delaunator.cpp
)

add_library(
        delaunator-lib-static
        STATIC
        delaunator.cpp)

find_library(
        log-lib
        log)


target_link_libraries(
        delaunator-lib
        delaunator-lib-static
        #android
        ${log-lib})
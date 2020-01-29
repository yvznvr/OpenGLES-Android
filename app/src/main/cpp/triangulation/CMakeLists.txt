cmake_minimum_required(VERSION 3.4.1)

add_library(
        triangulation-lib-static
        STATIC
        Triangulate.cpp)

find_library(
        log-lib
        log)



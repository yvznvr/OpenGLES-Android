cmake_minimum_required(VERSION 3.4.1)

set( delaunator_src_DIR ../delaunator )

set( delaunator_build_DIR ../delaunator/outputs )
file(MAKE_DIRECTORY ${delaunator_build_DIR})


add_subdirectory(${delaunator_src_DIR}
        ${delaunator_build_DIR} )

add_library( # Sets the name of the library.
        native-lib

        # Sets the library as a shared library.
        SHARED

        # Provides a relative path to your source file(s).
        native-lib.cpp
        DrawRectangle.cpp
        DrawRectangle.h
        ../delaunator/Triangulate.h)

find_library(log-lib
                log)

target_link_libraries( 
        native-lib
        delaunator-lib-static
        EGL
        GLESv2
        android
        ${log-lib})




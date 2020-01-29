cmake_minimum_required(VERSION 3.4.1)

set( triangulation_src_DIR ../triangulation )

set( triangulation_build_DIR ../triangulation/outputs )
file(MAKE_DIRECTORY ${triangulation_build_DIR})


add_subdirectory(${triangulation_src_DIR}
        ${triangulation_build_DIR} )

add_library( # Sets the name of the library.
        native-lib

        # Sets the library as a shared library.
        SHARED

        # Provides a relative path to your source file(s).
        native-lib.cpp
        DrawRectangle.cpp
        DrawRectangle.h
        ../triangulation/Triangulate.h)

find_library(log-lib
                log)

target_link_libraries( 
        native-lib
        triangulation-lib-static
        EGL
        GLESv2
        android
        ${log-lib})




cmake_minimum_required(VERSION 3.4.1)

set( lib_src_DIR ./opengl )

set( lib_build_DIR ../opengl/outputs )
file(MAKE_DIRECTORY ${lib_build_DIR})

add_subdirectory(${lib_src_DIR}
                ${lib_build_DIR} )


set( delaunator_src_DIR ./delaunator )

set( delaunator_build_DIR ../delaunator/outputs )
file(MAKE_DIRECTORY ${delaunator_build_DIR})


add_subdirectory(${delaunator_src_DIR}
                ${delaunator_build_DIR} )               




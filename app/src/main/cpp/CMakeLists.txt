cmake_minimum_required(VERSION 3.4.1)

# Sets lib_src_DIR to the path of the target CMake project.
set( lib_src_DIR ./opengl )

# Sets lib_build_DIR to the path of the desired output directory.
set( lib_build_DIR ../opengl/outputs )
file(MAKE_DIRECTORY ${lib_build_DIR})

# Adds the CMakeLists.txt file located in the specified directory
# as a build dependency.
add_subdirectory( # Specifies the directory of the CMakeLists.txt file.
                  ${lib_src_DIR}

                  # Specifies the directory for the build outputs.
                  ${lib_build_DIR} )


# Sets delaunator_src_DIR to the path of the target CMake project.
set( delaunator_src_DIR ./delaunator )

# Sets delaunator_build_DIR to the path of the desired output directory.
set( delaunator_build_DIR ../delaunator/outputs )
file(MAKE_DIRECTORY ${delaunator_build_DIR})

# Adds the CMakeLists.txt file located in the specified directory
# as a build dependency.
add_subdirectory( # Specifies the directory of the CMakeLists.txt file.
                  ${delaunator_src_DIR}

                  # Specifies the directory for the build outputs.
                  ${delaunator_build_DIR} )               




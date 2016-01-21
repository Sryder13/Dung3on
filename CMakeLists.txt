cmake_minimum_required (VERSION 3.0)
project (Dung3on)

# The version number.
set (VERSION_MAJOR 0)
set (VERSION_MINOR 1)

set (CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set (EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set (LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

# location of all the source files
set (SOURCE_FILES_DIR ${PROJECT_BINARY_DIR}/src)

# list of source files
set (SOURCE_FILES
	"${SOURCE_FILES_DIR}/main.cpp"
	)

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
	"${PROJECT_SOURCE_DIR}/config.hpp.in"
	"${SOURCE_FILES_DIR}/config.hpp"
	)

# add the binary tree to the search path for include files
# so that we will find config.h
include_directories("${SOURCE_FILES_DIR}")

# add the executable
add_executable (dung3on ${SOURCE_FILES})

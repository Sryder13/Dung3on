cmake_minimum_required (VERSION 3.0)
project (Dung3on)

# The version number.
set (VERSION_MAJOR 0)
set (VERSION_MINOR 1)

set (CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set (EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set (LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

# cmake modules
set (CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

# location of all the source files
set (SOURCE_FILES_DIR ${PROJECT_BINARY_DIR}/src)

# list of source files
set (SOURCE_FILES
	"${SOURCE_FILES_DIR}/main.cpp"
	"${SOURCE_FILES_DIR}/md2.cpp"
	"${SOURCE_FILES_DIR}/game.cpp"
	"${SOURCE_FILES_DIR}/texture.cpp"
	"${SOURCE_FILES_DIR}/resourcemanager.cpp"
	"${SOURCE_FILES_DIR}/gamemap.cpp"
	"${SOURCE_FILES_DIR}/entity.cpp"
	"${SOURCE_FILES_DIR}/controls.cpp"
	)

# include OpenGL
find_package (OpenGL REQUIRED)
include_directories (${OPENGL_INCLUDE_DIR})

# include GLEW
find_package (GLEW REQUIRED)
include_directories (${GLEW_INCLUDE_DIRS})

# include SDL2
find_package (SDL2 REQUIRED)
include_directories (${SDL2_INCLUDE_DIR})

# include SDL2 image
find_package (SDL2_image REQUIRED)
include_directories (${SDL2_IMAGE_INCLUDE_DIR})

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
target_link_libraries(dung3on ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY})

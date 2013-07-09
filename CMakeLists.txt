# minimum version of CMake needed (used version).
cmake_minimum_required(VERSION 2.8.9)

# Our project name: bool_network
project(bool_network)

set(BOOL_NETWORK_SOURCE_DIR ".")

# Enable debug symbols by default
if(CMAKE_BUILD_TYPE STREQUAL "")
    set(CMAKE_BUILD_TYPE "Debug")
endif()
message(STATUS "Building in '${CMAKE_BUILD_TYPE}' mode")

# Compile flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic -W -Wall -Wextra -Wold-style-cast -Woverloaded-virtual -Wfloat-equal -Wwrite-strings -Wpointer-arith -Wcast-align -Wconversion -Wredundant-decls -Winit-self -Wswitch-default -Wswitch-enum -Wundef -Wunused-parameter -O3")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

# Debug flags
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DDEBUG")
endif()

# bool_network include directory
include_directories("include")

# bool_network sources
file(GLOB_RECURSE BOOL_NETWORK_SOURCES ${BOOL_NETWORK_SOURCE_DIR}/src/*.cpp)
list(REMOVE_ITEM BOOL_NETWORK_SOURCES ${BOOL_NETWORK_SOURCE_DIR}/src/main.cpp)
set(BOOL_NETWORK_LIB "bool_network")
add_library(${BOOL_NETWORK_LIB} SHARED ${BOOL_NETWORK_SOURCES})

# CTags target
set(CTAGS_TARGET_NAME "tags")
set(CTAGS_SCRIPT "ctags.sh")
set(CTAGS_CMD ${CMAKE_CURRENT_SOURCE_DIR}/${CTAGS_SCRIPT})
add_custom_target(
    ${CTAGS_TARGET_NAME}
    COMMAND ${CTAGS_CMD})

# Doxygen target
find_package(Doxygen)
if(DOXYGEN_FOUND)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
add_custom_target(doc
${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
COMMENT "Generating API documentation with Doxygen" VERBATIM
)
endif(DOXYGEN_FOUND)

# Tests
add_subdirectory("tests")

# Examples
add_subdirectory("examples")

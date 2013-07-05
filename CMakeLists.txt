# minimum version of CMake needed (used version).
cmake_minimum_required(VERSION 2.6)

# Our project name: CellBool
project(CellBool)

set(CELLBOOL_SOURCE_DIR ".")

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

# CellBool include directory
include_directories("include")

# CellBool sources
file(GLOB_RECURSE CELLBOOL_SOURCES ${CELLBOOL_SOURCE_DIR}/src/*.cpp)
list(REMOVE_ITEM CELLBOOL_SOURCES ${CELLBOOL_SOURCE_DIR}/src/main.cpp)
set(CELLBOOL_LIB "CELLBOOL_lib")
add_library(${CELLBOOL_LIB} SHARED ${CELLBOOL_SOURCES})

# CTags target
set(CTAGS_TARGET_NAME "tags")
set(CTAGS_SCRIPT "ctags.sh")
set(CTAGS_CMD ${CMAKE_CURRENT_SOURCE_DIR}/${CTAGS_SCRIPT})
add_custom_target(
    ${CTAGS_TARGET_NAME}
    COMMAND ${CTAGS_CMD})

# Doxygen target
set(DOXYGEN_TARGET_NAME "doxygen")
set(DOXYGEN_FILE "Doxyfile")
set(DOXYGEN_CMD doxygen ${CMAKE_CURRENT_SOURCE_DIR}/${DOXYGEN_FILE})
add_custom_target(
    ${DOXYGEN_TARGET_NAME}
    COMMAND ${DOXYGEN_CMD})

# Tests
add_subdirectory("tests")

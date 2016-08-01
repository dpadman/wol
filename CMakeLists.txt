cmake_minimum_required(VERSION 2.8)
list(APPEND CMAKE_CXX_FLAGS "-g -Wall -Werror")
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_executable(wol wol.c)

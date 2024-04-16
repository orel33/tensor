cmake_minimum_required(VERSION 3.0)

project("tree" C)

include(CTest)
enable_testing()

set(CMAKE_C_FLAGS "-g -std=c99 -Wall")

add_library(tensor tensor.c tensor_aux.c)
add_executable(sample sample.c)
target_link_libraries(sample tensor)


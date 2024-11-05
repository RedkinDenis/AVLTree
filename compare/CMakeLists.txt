cmake_minimum_required(VERSION 3.11)
project(compare)

set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

add_executable(avl_bench avl_bench.cpp benchmark.hpp)
target_include_directories(avl_bench PUBLIC ${INCLUDE_DIR})

add_executable(set_bench set_bench.cpp benchmark.hpp)
target_include_directories(set_bench PUBLIC ${INCLUDE_DIR})
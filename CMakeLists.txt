# cmake -DCMAKE_BUILD_TYPE=Release -S . -B build

cmake_minimum_required(VERSION 3.10)
project(avltree)

set(CMAKE_CXX_STANDARD 17)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
include_directories(${INCLUDE_DIR})


# SET(SRCS
#     src/matrix.cpp
# )

# add_library(mtr STATIC ${SRCS})

add_executable(avltree.x main.cpp)                                                         
# target_link_libraries(avltree.x mtr)
target_link_libraries(avltree.x ${GTEST_LIBRARIES} pthread)

# cmake -DCMAKE_BUILD_TYPE=Release -S . -B build

cmake_minimum_required(VERSION 3.10)
project(avltree)

set(CMAKE_CXX_STANDARD 17)

find_package(GTest REQUIRED)

set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

SET(SRCS
    src/tree.cpp
)

add_library(tree STATIC ${SRCS})

target_include_directories(tree PUBLIC ${INCLUDE_DIR})

add_library(TEST STATIC ${SRCS})

target_include_directories(TEST PUBLIC ${GTEST_INCLUDE_DIRS})
target_include_directories(TEST PUBLIC ${INCLUDE_DIR})


add_library(UNIT_TEST STATIC ${SRCS})

target_include_directories(UNIT_TEST PUBLIC ${GTEST_INCLUDE_DIRS})
target_include_directories(UNIT_TEST PUBLIC ${INCLUDE_DIR})


add_executable(avltree.x main.cpp)                                                         
target_link_libraries(avltree.x tree)


add_executable(avltree.test main.cpp)                                                         
target_link_libraries(avltree.test TEST)
target_link_libraries(avltree.test ${GTEST_LIBRARIES} pthread)
target_compile_definitions(avltree.test PRIVATE FULL_TESTING)



add_executable(avltree.unit main.cpp)                                                         
target_link_libraries(avltree.unit UNIT_TEST)
target_link_libraries(avltree.unit ${GTEST_LIBRARIES} pthread)
target_compile_definitions(avltree.unit PRIVATE UNIT_TESTING)

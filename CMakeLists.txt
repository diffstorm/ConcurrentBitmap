cmake_minimum_required(VERSION 3.10)
project(BitmapTask)

set(CMAKE_CXX_STANDARD 11)

add_executable(BitmapSimulator main.cpp)

enable_testing()
add_subdirectory(googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(BitmapTest bitmap_test.cpp)
target_link_libraries(BitmapTest gtest gtest_main)
add_test(NAME BitmapTest COMMAND BitmapTest)

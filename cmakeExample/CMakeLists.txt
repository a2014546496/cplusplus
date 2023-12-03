cmake_minimum_required(VERSION 3.16)

project(cmakeExmaple)

set(CMAKE_BUILD_TYPE Debug)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(main main.cpp src/classOne.cpp)
cmake_minimum_required(VERSION 3.17)

project(Concurrency VERSION 1.0.0)

add_library(

    thread01.cpp
)

add_executable(cpp-compiler thread01.cpp)
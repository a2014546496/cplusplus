cmake_minimum_required(VERSION 3.16)

project(Concurrency VERSION 1.0.0)



add_executable(cpp-compiler thread01.cpp)

target_link_libraries(cpp-compiler pthread)
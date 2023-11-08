cmake_minimum_required(VERSION 3.16)


set(CMAKE_CXX_STANDARD 17)
project(Concurrency VERSION 1.0.0)



add_executable(cpp-compiler thread02.cpp)

target_link_libraries(cpp-compiler pthread)
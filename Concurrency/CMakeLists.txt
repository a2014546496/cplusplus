cmake_minimum_required(VERSION 3.16)


set(CMAKE_CXX_STANDARD 20)
project(Concurrency VERSION 1.0.0)
add_executable(mq src/Threadsafe_queue.cpp)
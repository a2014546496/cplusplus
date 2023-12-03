cmake_minimum_required(VERSION 3.16)


set(CMAKE_CXX_STANDARD 20)
project(Concurrency VERSION 1.0.0)


find_package(Boost REQUIRED COMPONENTS thread chrono)
include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})
MESSAGE(message ${Boost_INCLUDE_DIRS})
MESSAGE(message2 ${Boost_LIBRARY_DIRS})
add_executable(mq src/barrier.cpp)
target_link_libraries(mq ${Boost_LIBRARIES})
MESSAGE(message ${Boost_LIBRARIES})
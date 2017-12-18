cmake_minimum_required(VERSION 3.6)
project(TrafficSignalSimulator)

set(CMAKE_CXX_STANDARD 11)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

set(SOURCE_FILES main.cpp src/Simulation.cpp src/Road.cpp src/Intersection.cpp)
add_executable(TrafficSignalSimulator ${SOURCE_FILES})
target_link_libraries(TrafficSignalSimulator ${CURSES_LIBRARIES})
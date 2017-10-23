cmake_minimum_required(VERSION 2.8.9)

# Compiler Options Setup
project(Drivers)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Werror -Wextra -pedantic -lpthread")

# Includes
include_directories(Include/Interfaces)
include_directories(Include/Registers)
include_directories(Include/Sensors)
include_directories(Include/System)

# Created Shared Object Library
file(GLOB_RECURSE DRIVER_FILES "Src/*.cpp")
add_library(Drivers SHARED ${DRIVER_FILES})

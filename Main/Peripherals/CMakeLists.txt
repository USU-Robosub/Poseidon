cmake_minimum_required(VERSION 3.3)
project(Peripherals)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(include)
file(GLOB_RECURSE SOURCE_FILES "src/*.cpp")

add_executable(Peripherals ${SOURCE_FILES})
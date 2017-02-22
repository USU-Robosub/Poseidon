cmake_minimum_required(VERSION 2.8.9)
project(SLAM)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -pedantic") # -Werror

file(GLOB_RECURSE HEADER_FILES "include/*.h" "include/*.hpp")
file(GLOB_RECURSE SOURCE_FILES "src/*.cpp" "src/*.hpp" "src/*.h")
file(GLOB_RECURSE TEST_SOURCE_FILES "test/*.cpp" "test/*.hpp" "test/*.h")

add_library(slam STATIC ${HEADER_FILES} ${SOURCE_FILES})
add_executable(slam_tests ${HEADER_FILES} ${SOURCE_FILES} ${TEST_SOURCE_FILES})
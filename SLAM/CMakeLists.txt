cmake_minimum_required(VERSION 2.8.9)
project(SLAM)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -pedantic") # -Werror
set(TEST_RESOURCES_DIR "${PROJECT_SOURCE_DIR}/test_resources")

configure_file(test/_config.h.in ${PROJECT_SOURCE_DIR}/test/_config.h )

file(GLOB_RECURSE HEADER_FILES "include/*.h" "include/*.hpp")
file(GLOB_RECURSE SOURCE_FILES "src/*.cpp" "src/*.hpp" "src/*.h")
file(GLOB_RECURSE TEST_SOURCE_FILES "test/*.cpp" "test/*.hpp" "test/*.h")

# Declare the libraries and executable targets built from your sources
add_library(slam ${HEADER_FILES} ${SOURCE_FILES})
add_executable(slam_tests ${TEST_SOURCE_FILES})

# Link the slam library to the slam_tests executable
target_link_libraries(slam_tests slam)

include(catch.cmake)
include(opencv.cmake)


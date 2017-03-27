cmake_minimum_required(VERSION 2.8.9)
project(SLAM)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -pedantic") # -Werror

set(CATCH_INCLUDE_DIR ../Libraries/Catch/include)

get_filename_component(CATCH_INCLUDE_DIR ${CATCH_INCLUDE_DIR} ABSOLUTE)
if(EXISTS ${CATCH_INCLUDE_DIR})
  message("Catch library found at ${CATCH_INCLUDE_DIR}")
  message("SLAM unit tests will be built.")
  include_directories(${CATCH_INCLUDE_DIR})
else()
  message("Catch library NOT found at ${CATCH_INCLUDE_DIR}")
  message("To build SLAM unit tests, initialize submodule Catch.")
endif()

file(GLOB_RECURSE HEADER_FILES "include/*.h" "include/*.hpp")
file(GLOB_RECURSE SOURCE_FILES "src/*.cpp" "src/*.hpp" "src/*.h")
file(GLOB_RECURSE TEST_SOURCE_FILES "test/*.cpp" "test/*.hpp" "test/*.h")

add_library(slam STATIC ${HEADER_FILES} ${SOURCE_FILES})
add_executable(slam_tests ${HEADER_FILES} ${SOURCE_FILES} ${TEST_SOURCE_FILES})

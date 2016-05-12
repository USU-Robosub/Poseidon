cmake_minimum_required(VERSION 2.8.9)
project(Vision)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Werror -Wextra -pedantic -lpthread")

# get_filename_component(Vision_Path "include" ABSOLUTE)
# set(Vision_Includes "${CMAKE_CURRENT_SOURCE_DIR}/include")

include_directories(${Vision_Includes})

file(GLOB_RECURSE VISION_FILES "src/*.cpp")
add_library(Vision ${VISION_FILES})

add_executable(capture src/gateDetectorMain.cpp)
target_link_libraries(Vision)

cmake_minimum_required(VERSION 2.8.9)
project(PiVision)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Werror -Wextra -pedantic -lpthread")

include_directories("../Libraries/Json")
link_directories(../Libraries/Sockets/Build)
get_filename_component(Sockets_Path "../Libraries/Sockets/include" ABSOLUTE)
include_directories("${Sockets_Path}")

set(Vision_Includes "${CMAKE_CURRENT_SOURCE_DIR}/include")
include_directories(${Vision_Includes})

file(GLOB_RECURSE VISION_FILES "src/*.cpp")
add_library(Vision SHARED ${VISION_FILES})

find_package(OpenCV REQUIRED)

add_executable(capture gateDetectorMain.cpp)
target_link_libraries(Vision ${OpenCV_LIBS})
target_link_libraries(capture Sockets Vision)

cmake_minimum_required(VERSION 2.8.9)
project(SLAM)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -pedantic") #-Werror

file(GLOB_RECURSE SOURCE_FILES "src/*.cpp" "src/*.hpp" "src/*.h")

set(SOURCE_FILES
        src/telemetry/TelemetryProvider.h
        src/telemetry/TelemetryProvider.cpp
        src/telemetry/TelemetryPacket.hpp
        src/camera/ICameraFrameGenerator.h
        src/camera/CameraFrame.hpp
        src/depth/IDepthMapGenerator.h
        src/depth/DepthMap.hpp
        src/pose/Pose.hpp
        src/slam.h src/pose/IPoseGenerator.h)

set(TEST_SOURCE_FILES
        include/catch.hpp
        test/telemetry/TelemetryProviderTest.cpp
        test/test_main.cpp)

add_library(slam STATIC ${SOURCE_FILES})

add_executable(slam_tests ${SOURCE_FILES} ${TEST_SOURCE_FILES})
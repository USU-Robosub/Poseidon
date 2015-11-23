cmake_minimum_required(VERSION 3.3)
project(Peripherals)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")

# Shared Stuff

include_directories(include/Interfaces)

include_directories(include/Controllers)
file(GLOB_RECURSE CONTROLLER_FILES "src/Controllers/*.cpp")
add_library(Controllers ${CONTROLLER_FILES})

# Tests

add_subdirectory("tests/gtest-1.7.0")
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

include_directories(tests/Mocks/include)
file(GLOB_RECURSE MOCK_FILES "tests/Mocks/src/*.cpp")
add_library(Mocks ${MOCK_FILES})

file(GLOB_RECURSE TEST_FILES "tests/Specs/*.cpp")
add_executable(Specs ${TEST_FILES})

target_link_libraries(Specs gtest gtest_main)
target_link_libraries(Specs Mocks Controllers)
target_link_libraries(Mocks Controllers)

add_test(Test Specs)

# Production

include_directories(include/Drivers)
file(GLOB_RECURSE DRIVER_FILES "src/Drivers/*.cpp")
add_library(Drivers ${DRIVER_FILES})

include_directories(include/Bootstrap)
file(GLOB_RECURSE BOOTSTRAP_FILES "src/Bootstrap/*.cpp")
add_executable(Bootstrap ${BOOTSTRAP_FILES})

target_link_libraries(Bootstrap Drivers Controllers)
target_link_libraries(Drivers Controllers)
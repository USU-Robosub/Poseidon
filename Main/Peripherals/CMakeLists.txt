cmake_minimum_required(VERSION 3.3)
project(Peripherals)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(include)

file(GLOB_RECURSE CONTROLLER_FILES "src/Controllers/*.cpp")
add_library(Controllers ${CONTROLLER_FILES})

#file(GLOB_RECURSE DRIVER_FILES "src/Drivers/*.cpp")
#add_library(Drivers ${DRIVER_FILES})

#file(GLOB_RECURSE BOOTSTRAP_FILES "src/Bootstrap/*.cpp")
#add_executable(Peripherals ${BOOTSTRAP_FILES})

#target_link_libraries(Peripherals Drivers Controllers)
#target_link_libraries(Drivers Controllers)

file(GLOB_RECURSE MOCK_DRIVER_FILES "tests/Mocks/Drivers/*.cpp")
add_library(MockDrivers ${MOCK_DRIVER_FILES})

add_subdirectory("tests/gtest-1.7.0")
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

file(GLOB_RECURSE TEST_FILES "tests/Specs/*.cpp")
add_executable(Specs ${TEST_FILES})

target_link_libraries(Specs gtest gtest_main)
target_link_libraries(Specs MockDrivers Controllers)
target_link_libraries(MockDrivers Controllers)

add_test(Test Specs)
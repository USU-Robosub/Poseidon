cmake_minimum_required(VERSION 3.0)
project(Peripherals)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Werror -Wextra -pedantic -lpthread")

# Shared Stuff

include_directories(include/Interfaces)

include_directories(include/Peripherals)
file(GLOB_RECURSE PERIPHERAL_FILES "src/Peripherals/*.cpp")
add_library(Peripherals SHARED ${PERIPHERAL_FILES})

# Tests

add_subdirectory("tests/gtest-1.7.0")
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

include_directories(tests/Mocks/include)
file(GLOB_RECURSE MOCK_FILES "tests/Mocks/src/*.cpp")
add_library(Mocks SHARED ${MOCK_FILES})

file(GLOB_RECURSE TEST_FILES "tests/Specs/*.cpp")
add_executable(Specs ${TEST_FILES})

target_link_libraries(Specs gtest gtest_main)
target_link_libraries(Specs Mocks Peripherals)
target_link_libraries(Mocks Peripherals)

add_test(Test Specs)

# Production

include_directories(include/Drivers)
file(GLOB_RECURSE DRIVER_FILES "src/Drivers/*.cpp")
add_library(Drivers SHARED ${DRIVER_FILES})
set_target_properties(Drivers PROPERTIES COMPILE-FLAGS "-mindgem")

include_directories(include/Bootstrap)
file(GLOB_RECURSE BOOTSTRAP_FILES "src/Bootstrap/*.cpp")
add_executable(Bootstrap ${BOOTSTRAP_FILES})

target_link_libraries(Bootstrap Drivers Peripherals)
target_link_libraries(Drivers Peripherals)

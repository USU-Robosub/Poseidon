cmake_minimum_required(VERSION 2.8.9)
project(Peripherals)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11 -Wall -Werror -Wextra -pedantic -lpthread")

# Shared Stuff

include_directories(include/Interfaces)

include_directories(include/Peripherals)
file(GLOB_RECURSE PERIPHERAL_FILES "src/Peripherals/*.cpp")
add_library(Peripherals SHARED ${PERIPHERAL_FILES})

# Tests

add_subdirectory("tests/gtest-1.7.0")
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

#include_directories(tests/Mocks/include)
#file(GLOB_RECURSE MOCK_FILES "tests/Mocks/src/*.cpp")
#add_library(Mocks SHARED ${MOCK_FILES})

file(GLOB_RECURSE TEST_FILES "tests/Specs/*.cpp")
add_executable(Specs ${TEST_FILES})

target_link_libraries(Specs gtest gtest_main)
#target_link_libraries(Specs Mocks Peripherals)
#target_link_libraries(Mocks Peripherals)

add_test(Test Specs)

# Production
include_directories(../../Drivers/Include/Interfaces)
include_directories(../../Drivers/Include/Registers)
include_directories(../../Drivers/Include/Sensors)
include_directories(../../Drivers/Include/System)
link_directories(../../Drivers/Build)

include_directories(include/Drivers)
file(GLOB_RECURSE DRIVER_FILES "src/Drivers/*.cpp")
add_library(Wrappers SHARED ${DRIVER_FILES})

include_directories(include/Sockets)
file(GLOB_RECURSE SOCKET_FILES "src/Sockets/*.cpp")
add_library(Sockets SHARED ${SOCKET_FILES})

include_directories(include/Bootstrap)
file(GLOB_RECURSE BOOTSTRAP_FILES "src/Bootstrap/*.cpp")
add_executable(Bootstrap ${BOOTSTRAP_FILES})

target_link_libraries(Bootstrap Wrappers Peripherals Drivers)
target_link_libraries(Wrappers Peripherals)

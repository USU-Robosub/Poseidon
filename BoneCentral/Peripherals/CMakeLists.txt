cmake_minimum_required(VERSION 2.8.9)
project(Peripherals)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11 -Wall -Werror -Wextra -pedantic -lpthread")

# Shared Stuff

include_directories(include/Interfaces)

include_directories(include/Peripherals)
file(GLOB_RECURSE PERIPHERAL_FILES "src/Peripherals/*.cpp")
add_library(Peripherals SHARED ${PERIPHERAL_FILES})

link_directories(../../Drivers/Build)

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

add_subdirectory(Peripherals.Sockets)
include_directories(${Socket_Includes})

add_subdirectory(Peripherals.I2CAdaptors)
include_directories(${I2CAdaptor_Includes})

add_subdirectory(Peripherals.SerialAdaptors)
include_directories(${SerialAdaptor_Includes})

add_subdirectory(Peripherals.Assembler)
include_directories(${Assembler_Includes})

add_executable(Peripherals.Start main.cpp)
target_link_libraries(Peripherals.Start Peripherals.Assembler)

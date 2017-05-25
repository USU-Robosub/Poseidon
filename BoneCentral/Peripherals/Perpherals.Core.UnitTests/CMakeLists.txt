cmake_minimum_required(VERSION 2.8.9)
project(Peripherals)

link_directories("../../../GoogleTest")
include_directories(${GTEST_DIR}/include)

#include_directories(Perpherals.Core.UnitTests/Mocks/include)
#file(GLOB_RECURSE MOCK_FILES "Perpherals.Core.UnitTests/Mocks/src/*.cpp")
#add_library(Mocks SHARED ${MOCK_FILES})

file(GLOB_RECURSE TEST_FILES "Perpherals.Core.UnitTests/Specs/*.cpp")
add_executable(Specs ${TEST_FILES})

target_link_libraries(Specs gtest gtest_main)
#target_link_libraries(Specs Mocks Peripherals.Core)
#target_link_libraries(Mocks Peripherals.Core)

add_test(Test Specs)
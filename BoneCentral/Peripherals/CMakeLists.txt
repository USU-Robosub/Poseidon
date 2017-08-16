cmake_minimum_required(VERSION 2.8.9)
project(Peripherals)

option(mock_drivers "Mock drivers" OFF)
option(tests "Build tests" OFF)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11 -Wall -Werror -Wextra -pedantic -pthread")

#add_definitions(-DDEBUG)

if(${mock_drivers})
  link_directories(../../Libraries/MockDrivers/build)
else()
  link_directories(../../Libraries/Drivers/Build)
endif()
link_directories(../../Libraries/Sockets/Build)
include_directories(../../Libraries/json/src)

set(SOS_ROOT ${Peripherals_SOURCE_DIR}/../../SOS/cpp)
find_library(SOS NAMES libSOS.a PATHS ${SOS_ROOT}/build)
include_directories(${SOS_ROOT}/include)

add_subdirectory(Peripherals.Core)
include_directories(${Core_Includes})

add_subdirectory(Peripherals.I2CAdaptors)
include_directories(${I2CAdaptor_Includes})

add_subdirectory(Peripherals.SerialAdaptors)
include_directories(${SerialAdaptor_Includes})

add_subdirectory(Peripherals.Assembler)
include_directories(${Assembler_Includes})

add_executable(Peripherals main.cpp)
target_link_libraries(Peripherals ${SOS} Sockets Peripherals.Assembler)

if(${tests})
  file(GLOB_RECURSE TEST_FILES "*.spec.cpp")

  set(GTEST_ROOT ${Peripherals_SOURCE_DIR}/../../Libraries/googletest/googletest)
  set(GMOCK_ROOT ${Peripherals_SOURCE_DIR}/../../Libraries/googletest/googlemock)

  find_library(GTEST NAMES libgtest.a PATHS ${GTEST_ROOT}/build)
  find_library(GMOCK NAMES libgmock.a PATHS ${GMOCK_ROOT}/build)

  include_directories(${GTEST_ROOT}/include)
  include_directories(${GMOCK_ROOT}/include)

  add_executable(Peripherals_tests test_main.cpp ${TEST_FILES} ${SOURCE_FILES})
  target_link_libraries(Peripherals_tests  ${SOS} Sockets Peripherals.Assembler ${GTEST} ${GMOCK})
endif()

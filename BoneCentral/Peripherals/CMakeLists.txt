cmake_minimum_required(VERSION 2.8.9)
project(Peripherals)

option(mock_drivers "Mock drivers" OFF)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11 -Wall -Werror -Wextra -pedantic -pthread")

#add_definitions(-DDEBUG)

if(${mock_drivers})
  link_directories(../../Libraries/MockDrivers/build)
else()
  link_directories(../../Libraries/Drivers/Build)
endif()

link_directories(../../Libraries/Sockets/Build)
include_directories(../../Libraries/Json)

add_subdirectory(Peripherals.Core)
include_directories(${Core_Includes})

add_subdirectory(Peripherals.I2CAdaptors)
include_directories(${I2CAdaptor_Includes})

add_subdirectory(Peripherals.SerialAdaptors)
include_directories(${SerialAdaptor_Includes})

add_subdirectory(Peripherals.Assembler)
include_directories(${Assembler_Includes})

add_executable(Peripherals main.cpp)
target_link_libraries(Peripherals Sockets Peripherals.Assembler)

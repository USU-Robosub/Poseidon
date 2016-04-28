cmake_minimum_required(VERSION 2.8.9)
project(Peripherals)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11 -Wall -Werror -Wextra -pedantic -lpthread")

link_directories(../../Drivers/Build)
include_directories(lib)

add_subdirectory(Peripherals.Core)
include_directories(${Core_Includes})

add_subdirectory(Peripherals.Sockets)
include_directories(${Socket_Includes})

add_subdirectory(Peripherals.I2CAdaptors)
include_directories(${I2CAdaptor_Includes})

add_subdirectory(Peripherals.SerialAdaptors)
include_directories(${SerialAdaptor_Includes})

add_subdirectory(Peripherals.Assembler)
include_directories(${Assembler_Includes})

add_executable(Peripherals main.cpp)
target_link_libraries(Peripherals Peripherals.Assembler)

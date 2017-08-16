cmake_minimum_required(VERSION 2.8.9)
project(Peripherals.Assembler)

get_filename_component(Sockets_Path "../../../Libraries/Sockets/include" ABSOLUTE)

set(Assembler_Includes
		"${Sockets_Path}"
		"${CMAKE_CURRENT_SOURCE_DIR}/include")
include_directories(${Assembler_Includes})
file(GLOB_RECURSE ASSEMBLER_FILES "src/*.cpp")
add_library(Peripherals.Assembler SHARED ${ASSEMBLER_FILES})
target_link_libraries(Peripherals.Assembler Peripherals.I2CAdaptors Peripherals.SerialAdaptors Peripherals.Core Sockets ${SOS})
set(Assembler_Includes ${Assembler_Includes} PARENT_SCOPE)

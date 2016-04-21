cmake_minimum_required(VERSION 2.8.9)
project(Peripherals.Core)

set(Core_Includes "${CMAKE_CURRENT_SOURCE_DIR}/include" "${CMAKE_CURRENT_SOURCE_DIR}/include/Interfaces")
include_directories(${Core_Includes})
file(GLOB_RECURSE CORE_FILES "src/*.cpp")
add_library(Peripherals.Core ${CORE_FILES})
set(Core_Includes ${Core_Includes} PARENT_SCOPE)


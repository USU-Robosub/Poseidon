cmake_minimum_required(VERSION 2.8.9)
project(Peripherals.SerialAdaptors)

set(SerialAdaptor_Includes "${CMAKE_CURRENT_SOURCE_DIR}/include")
include_directories(${SerialAdaptor_Includes})
file(GLOB_RECURSE ADAPTOR_FILES "src/*.cpp")
add_library(Peripherals.SerialAdaptors SHARED ${ADAPTOR_FILES})
target_link_libraries(Peripherals.SerialAdaptors Peripherals.Core)
set(SerialAdaptor_Includes ${SerialAdaptor_Includes} PARENT_SCOPE)
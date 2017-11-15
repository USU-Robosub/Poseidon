cmake_minimum_required(VERSION 2.8.9)
project(Peripherals.Api)

set(Api_Includes "${CMAKE_CURRENT_SOURCE_DIR}/include")
include_directories(${Api_Includes})
file(GLOB_RECURSE ADAPTOR_FILES "src/*.cpp")
add_library(Peripherals.Api SHARED ${ADAPTOR_FILES})
target_link_libraries(Peripherals.Api Peripherals.Core)
set(Api_Includes ${Api_Includes} PARENT_SCOPE)

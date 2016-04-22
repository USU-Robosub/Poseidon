cmake_minimum_required(VERSION 2.8.9)
project(Peripherals.Sockets)

set(Socket_Includes "${CMAKE_CURRENT_SOURCE_DIR}/include")
include_directories(${Socket_Includes})
file(GLOB_RECURSE SOCKET_FILES "src/*.cpp")
add_library(Peripherals.Sockets ${SOCKET_FILES})
set(Socket_Includes ${Socket_Includes} PARENT_SCOPE)
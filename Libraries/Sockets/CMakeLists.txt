cmake_minimum_required(VERSION 2.8.9)

# Compiler Options Setup
project(Sockets)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Werror -Wextra -pedantic -lpthread")

# Includes
set(Socket_Includes "${CMAKE_CURRENT_SOURCE_DIR}/include")
include_directories(${Socket_Includes})

# Creates Shared Object Library
file(GLOB_RECURSE SOCKET_FILES "src/*.cpp")
add_library(Sockets SHARED ${SOCKET_FILES})

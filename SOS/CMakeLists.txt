cmake_minimum_required (VERSION 2.8.12)
project (SOS)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")

include_directories(${SOS_SOURCE_DIR}/Core/include)
include_directories(${SOS_SOURCE_DIR}/HubFactories/include)
include_directories(${SOS_SOURCE_DIR}/Hubs/include)
include_directories(${SOS_SOURCE_DIR}/PipeFactories/include)
include_directories(${SOS_SOURCE_DIR}/Pipes/include)

file(GLOB_RECURSE SOURCE_FILES "*.cpp")
file(GLOB_RECURSE TEST_FILES "*.spec.cpp")

LIST(REMOVE_AT SOURCE_FILES 0)
#message("${SOURCE_FILES}")

add_executable(SOS ${SOURCE_FILES})

#include(${SOS_SOURCE_DIR}/../TestingFrameworks/googletest/CMakeLists.txt)
#add_executable(SOS_tests ${SOURCE_FILES} ${TEST_FILES})
#target_link_libraries(SOS_tests ${DSO_LIBRARY} gmock)

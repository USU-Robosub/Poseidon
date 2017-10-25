cmake_minimum_required (VERSION 2.8.12)
project (SOSdemo)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11 -pthread")

set(SOS_ROOT ${SOSdemo_SOURCE_DIR}/../)

find_library(SOS NAMES libSOS.a PATHS ${SOS_ROOT}/build)

include_directories(${SOS_ROOT}/include)
include_directories(${SOSdemo_SOURCE_DIR}/../../../Libraries/json/src)

file(GLOB_RECURSE SOURCE_FILES "*.cpp")

# remove CMakeCXXCompilerId.cpp and test files
foreach(SOURCE_FILE ${SOURCE_FILES})
  if(SOURCE_FILE MATCHES "CMakeCXXCompilerId|spec.cpp")
    LIST(REMOVE_ITEM SOURCE_FILES ${SOURCE_FILE})
  endif()
endforeach()

add_executable(SOSdemo ${SOURCE_FILES})
target_link_libraries(SOSdemo ${SOS})

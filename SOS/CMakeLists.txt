cmake_minimum_required (VERSION 2.8.12)
project (SOS)

option(tests "Build tests" OFF)
#find_package(GTest REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11 -pthread")

include_directories(${SOS_SOURCE_DIR}/Core/include)
include_directories(${SOS_SOURCE_DIR}/Connections/include)
include_directories(${SOS_SOURCE_DIR}/Nodes/include)

file(GLOB_RECURSE SOURCE_FILES "*.cpp")
file(GLOB_RECURSE TEST_FILES "*.spec.cpp")

# remove CMakeCXXCompilerId.cpp and test files
foreach(SOURCE_FILE ${SOURCE_FILES})
  if(SOURCE_FILE MATCHES "CMakeCXXCompilerId|spec.cpp")
    LIST(REMOVE_ITEM SOURCE_FILES ${SOURCE_FILE})
  endif()
endforeach()
#message("${SOURCE_FILES}")

add_executable(SOS ${SOURCE_FILES})

if(${tests})
  # remove main.cpp
  foreach(SOURCE_FILE ${SOURCE_FILES})
    if(SOURCE_FILE MATCHES "main.cpp")
      LIST(REMOVE_ITEM SOURCE_FILES ${SOURCE_FILE})
    endif()
  endforeach()

  find_library(GTEST NAMES "libgtest.a" PATHS "${SOS_SOURCE_DIR}/../Libraries/googletest/googletest/build")
  find_library(GMOCK NAMES "libgmock.a" PATHS "${SOS_SOURCE_DIR}/../Libraries/googletest/googlemock/build")

  include_directories("${SOS_SOURCE_DIR}/../Libraries/googletest/googletest/include")
  include_directories("${SOS_SOURCE_DIR}/../Libraries/googletest/googlemock/include")

  add_executable(SOStests ${TEST_FILES} ${SOURCE_FILES})
  target_link_libraries(SOStests ${GTEST} ${GMOCK})
endif()

cmake_minimum_required (VERSION 2.8.12)
project (SOS)

option(tests "Build tests" OFF)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11 -pthread")

include_directories(${SOS_SOURCE_DIR}/include)
include_directories(${SOS_SOURCE_DIR}/../../Libraries/json/src)

file(GLOB_RECURSE SOURCE_FILES "src/*.cpp")

# remove CMakeCXXCompilerId.cpp and test files
foreach(SOURCE_FILE ${SOURCE_FILES})
  if(SOURCE_FILE MATCHES "CMakeCXXCompilerId|spec.cpp")
    LIST(REMOVE_ITEM SOURCE_FILES ${SOURCE_FILE})
  endif()
endforeach()

add_library(SOS ${SOURCE_FILES})

if(${tests})
  include_directories(${SOS_SOURCE_DIR}/mocks)

  file(GLOB_RECURSE TEST_FILES "*.spec.cpp")

  set(GTEST_ROOT ${SOS_SOURCE_DIR}/../../Libraries/googletest/googletest)
  set(GMOCK_ROOT ${SOS_SOURCE_DIR}/../../Libraries/googletest/googlemock)

  find_library(GTEST NAMES libgtest.a PATHS ${GTEST_ROOT}/build)
  find_library(GMOCK NAMES libgmock.a PATHS ${GMOCK_ROOT}/build)

  include_directories(${GTEST_ROOT}/include)
  include_directories(${GMOCK_ROOT}/include)

  add_executable(SOStests test_main.cpp ${TEST_FILES}) # ${SOURCE_FILES}
  target_link_libraries(SOStests SOS ${GTEST} ${GMOCK})
endif()

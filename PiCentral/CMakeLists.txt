cmake_minimum_required(VERSION 2.8.12)
project(PiCentral)

option(tests "Build tests" OFF)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11 -Wall -Werror -Wextra -pedantic -pthread")

include_directories(${PiCentral_SOURCE_DIR}/include)

file(GLOB_RECURSE SOURCE_FILES "src/*.cpp")

# remove CMakeCXXCompilerId.cpp and test files
foreach(SOURCE_FILE ${SOURCE_FILES})
  if(SOURCE_FILE MATCHES "CMakeCXXCompilerId|spec.cpp")
    LIST(REMOVE_ITEM SOURCE_FILES ${SOURCE_FILE})
  endif()
endforeach()

set(VISION_ROOT ${PiCentral_SOURCE_DIR}/../vision)
find_library(Vision NAMES libvision.a PATHS ${VISION_ROOT}/build)
include_directories(${VISION_ROOT}/include)

add_executable(PiCentral src/main.cpp ${SOURCE_FILES})

if(${tests})
  include_directories(${PiCentral_SOURCE_DIR}/mocks)

  file(GLOB_RECURSE TEST_FILES "*.spec.cpp")

  set(GTEST_ROOT ${PiCentral_SOURCE_DIR}/../Libraries/googletest/googletest)
  set(GMOCK_ROOT ${PiCentral_SOURCE_DIR}/../Libraries/googletest/googlemock)

  find_library(GTEST NAMES libgtest.a PATHS ${GTEST_ROOT}/build)
  find_library(GMOCK NAMES libgmock.a PATHS ${GMOCK_ROOT}/build)

  include_directories(${GTEST_ROOT}/include)
  include_directories(${GMOCK_ROOT}/include)

  add_executable(PiCentralTests test_main.cpp ${TEST_FILES})
  target_link_libraries(PiCentralTests ${GTEST} ${GMOCK})
endif()
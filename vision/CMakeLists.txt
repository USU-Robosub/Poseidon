cmake_minimum_required (VERSION 2.8.12)
project (Vision)

option(tests "Build tests" OFF)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11 -pthread")

include_directories(${Vision_SOURCE_DIR}/include)

file(GLOB_RECURSE SOURCE_FILES "src/*.cpp")

# remove CMakeCXXCompilerId.cpp and test files
foreach(SOURCE_FILE ${SOURCE_FILES})
  if(SOURCE_FILE MATCHES "CMakeCXXCompilerId|spec.cpp")
    LIST(REMOVE_ITEM SOURCE_FILES ${SOURCE_FILE})
  endif()
endforeach()

add_library(Vision ${SOURCE_FILES})

find_package(OpenCV REQUIRED)

target_link_libraries(Vision ${OpenCV_LIBS})

if(${tests})
  include_directories(${Vision_SOURCE_DIR}/mocks)

  file(GLOB_RECURSE TEST_FILES "*.spec.cpp")

  set(GTEST_ROOT ${Vision_SOURCE_DIR}/../Libraries/googletest/googletest)
  set(GMOCK_ROOT ${Vision_SOURCE_DIR}/../Libraries/googletest/googlemock)

  find_library(GTEST NAMES libgtest.a PATHS ${GTEST_ROOT}/build)
  find_library(GMOCK NAMES libgmock.a PATHS ${GMOCK_ROOT}/build)

  include_directories(${GTEST_ROOT}/include)
  include_directories(${GMOCK_ROOT}/include)

  add_executable(VisionTests test_main.cpp ${TEST_FILES})
  target_link_libraries(VisionTests Vision ${GTEST} ${GMOCK})
endif()

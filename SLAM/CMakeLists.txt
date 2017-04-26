cmake_minimum_required(VERSION 2.8.9)
project(SLAM)

include(macros.cmake)

set(BUILD_TYPE Release)
if(NOT DEFINED SHOW_WARNINGS)
  set(SHOW_WARNINGS FALSE)
endif()
if(${SHOW_WARNINGS})
  set(showWarningsMessage "Enabled")
  set(CMAKE_CXX_FLAGS "${SSE_FLAGS} -O3 -g -std=c++11 -pthread -Wall -Wextra -pedantic") # -Werror
else()
  set(showWarningsMessage "Disabled")
  set(CMAKE_CXX_FLAGS "${SSE_FLAGS} -O3 -g -std=c++11 -pthread -w") # -Wall -Wextra -pedantic -Werror
endif()

check_package(OpenCV REQUIRED)
check_package(Eigen3 REQUIRED)
check_package(Boost REQUIRED)

#find_package(Boost COMPONENTS system REQUIRED)

#DSO Library
find_library(DSO_LIBRARY libdso.a ${DSO_DIR}/build/lib)
if(NOT DEFINED DSO_INCLUDE_DIR)
  get_filename_component(DSO_INCLUDE_DIR ${DSO_DIR}/src ABSOLUTE)
endif()
if(NOT DEFINED Sophus_INCLUDE_DIR)
  get_filename_component(Sophus_INCLUDE_DIR ${DSO_DIR}/thirdparty/Sophus ABSOLUTE)
endif()
check_library("DSO" DSO_DIR DSO_LIBRARY DSO_INCLUDE_DIR Sophus_INCLUDE_DIR REQUIRED)

#Catch Library
if(NOT DEFINED CATCH_INCLUDE_DIR)
  get_filename_component(CATCH_INCLUDE_DIR ../Libraries/Catch/include ABSOLUTE)
endif()
check_library("CATCH" CATCH_INCLUDE_DIR)

message(" ")
message(BoldYellow "--- USU Robosub SLAM module ---")
message(BoldCyan "Show compiler warnings: [${showWarningsMessage}]")
message(BoldCyan "SLAM static library status: [Will Build]")
if(${CATCH_FOUND})
  message(BoldCyan "Unit test status: [Will Build]")
  include_directories(${CATCH_INCLUDE_DIR})
else()
  message(BoldMagenta "Unit test status: [Missing Library]")
  message(BoldMagenta "To build SLAM unit tests, initialize submodule Catch.")
endif()

set(TEST_RESOURCES_DIR "${PROJECT_SOURCE_DIR}/test_resources")

configure_file(test/_config.h.in ${PROJECT_SOURCE_DIR}/test/_config.h )

get_filename_component(PROJECT_INLUDE_DIR "include" ABSOLUTE)
HEADER_DIRECTORIES(PROJECT_INLUDE_DIR) # allows the include folder to have sub-folders

file(GLOB_RECURSE SOURCE_FILES "src/*.cpp")
file(GLOB_RECURSE TEST_SOURCE_FILES "test/*.cpp")

include_directories(
  ${OpenCV_INCLUDE_DIRS}
  ${EIGEN3_INCLUDE_DIR}
  ${DSO_INCLUDE_DIR}
  ${Sophus_INCLUDE_DIR}
  ${PROJECT_INLUDE_DIR}
)

add_library(slam ${SOURCE_FILES})
target_link_libraries(slam ${DSO_LIBRARY} ${OpenCV_LIBS} boost_system boost_thread)

if(${CATCH_FOUND})
  add_executable(slam_tests ${TEST_SOURCE_FILES})
  target_link_libraries(slam_tests slam ${OpenCV_LIBS}) # boost_system boost_thread -lssl)
endif()

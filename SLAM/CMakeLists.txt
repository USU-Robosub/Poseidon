cmake_minimum_required(VERSION 2.8.9)
project(SLAM)

set(BUILD_TYPE Release)
if(NOT DEFINED SHOW_WARNINGS)
  set(SHOW_WARNINGS FALSE)
endif()
if(${SHOW_WARNINGS})
  message("Compiler warnings enabled.")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -pedantic") # -Werror
else()
  message("Compiler warnings disabled.")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -w") # -Wall -Wextra -pedantic -Werror
endif()

find_package(Eigen3 REQUIRED)
find_package(OpenCV REQUIRED)

if(NOT WIN32)
  string(ASCII 27 Esc)
  set(ColourReset "${Esc}[m")
  set(ColourBold  "${Esc}[1m")
  set(Red         "${Esc}[31m")
  set(Green       "${Esc}[32m")
  set(Yellow      "${Esc}[33m")
  set(Blue        "${Esc}[34m")
  set(Magenta     "${Esc}[35m")
  set(Cyan        "${Esc}[36m")
  set(White       "${Esc}[37m")
  set(BoldRed     "${Esc}[1;31m")
  set(BoldGreen   "${Esc}[1;32m")
  set(BoldYellow  "${Esc}[1;33m")
  set(BoldBlue    "${Esc}[1;34m")
  set(BoldMagenta "${Esc}[1;35m")
  set(BoldCyan    "${Esc}[1;36m")
  set(BoldWhite   "${Esc}[1;37m")
endif()

function(check_library name)
  set(NO_VALUE_ERROR "[No value given]")
  message("")
  message("${BoldYellow}Checking ${name} library status...${ColourReset}")
  foreach(path ${ARGV})
    if(${path} STREQUAL REQUIRED)
      set(_isRequired TRUE)
    endif()
    if(NOT ${path} STREQUAL ${name} AND NOT ${path} STREQUAL REQUIRED)
      if(${path})
        get_filename_component(path_loc ${${path}} ABSOLUTE)
      else()
        set(path_loc ${NO_VALUE_ERROR})
      endif()
      if(EXISTS ${path_loc})
        message("${BoldGreen}[Found] ${path}: ${path_loc}${ColourReset}")
      else()
        message("${BoldMagenta}[Not Found] ${path}: ${path_loc}${ColourReset}")
        set(LIBRARY_${name}-NOTFOUND TRUE PARENT_SCOPE)
        set(LIBRARY_NOTFOUND TRUE)
      endif()
      if(NOT ${path_loc} EQUAL NO_VALUE_ERROR AND NOT IS_ABSOLUTE ${${path}})
        #Set the original path the absolute version
        set(${path} ${path_loc} PARENT_SCOPE)
      endif()
    endif()
  endforeach()
  if(LIBRARY_NOTFOUND)
    message("${BoldRed}${name} library status: [Failed]${ColourReset}")
    if(_isRequired)
      message(FATAL_ERROR "${BoldRed}Some parts of the library \"${name}\" could not be found. Because it is required, cmake project configuration cannot continue.${ColourReset}")
    endif()
  else()
    message("${BoldCyan}${name} library status: [Ready]${ColourReset}")
  endif()
endfunction(check_library)

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
get_filename_component(CATCH_INCLUDE_DIR ../Libraries/Catch/include ABSOLUTE)
check_library("CATCH" CATCH_INCLUDE_DIR)
if(NOT DEFINED LIBRARY_CATCH-NOTFOUND)
  message("SLAM unit tests will be built.")
  include_directories(${CATCH_INCLUDE_DIR})
else()
  message("SLAM unit tests will not be built. To build SLAM unit tests, initialize submodule Catch.")
endif()

get_filename_component(PROJECT_INLUDE_DIR "include" ABSOLUTE)

file(GLOB_RECURSE SOURCE_FILES "src/*.cpp" "src/*.hpp" "src/*.h")
file(GLOB_RECURSE TEST_SOURCE_FILES "test/*.cpp" "test/*.hpp" "test/*.h")

include_directories(
  ${OpenCV_INCLUDE_DIRS}
  ${EIGEN3_INCLUDE_DIR}
  ${DSO_INCLUDE_DIR}
  ${Sophus_INCLUDE_DIR}
  ${PROJECT_INLUDE_DIR}
)

add_library(slam STATIC ${SOURCE_FILES})
add_executable(slam_tests ${SOURCE_FILES} ${TEST_SOURCE_FILES})

target_link_libraries(slam ${DSO_LIBRARY} ${OpenCV_LIBS})
target_link_libraries(slam_tests ${DSO_LIBRARY} ${OpenCV_LIBS})

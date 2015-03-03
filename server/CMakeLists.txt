cmake_minimum_required(VERSION 2.6)

project(RCServer)

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS "-g -O3 --std=c++11 -Wno-c++98-compat-pedantic -pedantic -Weverything -Wno-unused-parameter -Wno-global-constructors -Wno-exit-time-destructors -Wno-non-virtual-dtor -Wno-weak-vtables -Wno-padded -Wno-cast-align -Wno-gnu -Wno-nested-anon-types -Wno-documentation-unknown-command -Wno-unknown-pragmas")
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS "-g -O3 --std=c++11 -Wall -Wextra -Wdouble-promotion -Wfloat-equal -Wunsafe-loop-optimizations -Wno-unused-parameter")
endif()

#https://stackoverflow.com/questions/13638408/cmake-override-compile-flags-for-single-files
SET (JSONCPP_CPP libs/jsoncpp-1.1.0/jsoncpp.cpp)
set_source_files_properties(${JSONCPP_CPP} PROPERTIES COMPILE_FLAGS -w)

include_directories(. libs/jsoncpp-1.1.0)

#organized by importance
add_executable(RCServer
    main.cpp
    RCServer.cpp

    ${JSONCPP_CPP}
)

target_link_libraries(RCServer pthread)

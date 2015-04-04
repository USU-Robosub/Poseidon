# The minimum CMake version we need to use
cmake_minimum_required(VERSION 2.6)


# Our project's name
project(RCServer)


if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS "-g -O3 --std=c++0x -Wno-c++98-compat-pedantic -pedantic -Weverything -Wno-deprecated-declarations -Wno-unused-parameter -Wno-global-constructors -Wno-exit-time-destructors -Wno-non-virtual-dtor -Wno-weak-vtables -Wno-padded -Wno-cast-align -Wno-gnu -Wno-nested-anon-types -Wno-documentation-unknown-command -Wno-unknown-pragmas -Wno-documentation-deprecated-sync")
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS "-g -O3 --std=c++0x -Wall -Wextra -Wdouble-promotion -Wfloat-equal -Wno-deprecated-declarations -Wunsafe-loop-optimizations -Wno-unused-parameter")
endif()


#https://stackoverflow.com/questions/13638408/cmake-override-compile-flags-for-single-files
SET(JSONCPP_CPP ../libs/jsoncpp-1.5.0/jsoncpp.cpp)
set_source_files_properties(${JSONCPP_CPP} PROPERTIES COMPILE_FLAGS "-w")


# -L/var/lib/gems/1.9.1/gems/rice-1.7.0/ruby/lib/lib
# -Lrice
include_directories(
    #/var/lib/gems/1.9.1/gems/rice-1.7.0
    #/var/lib/gems/1.9.1/gems/rice-1.7.0/rice
    #/var/lib/gems/1.9.1/gems/rice-1.7.0/ruby/lib/include
    #/usr/include/ruby-1.9.1
    #/usr/include/ruby-1.9.1/ruby
    #/usr/include/ruby-1.9.1/arm-linux-eabihf
    .
    libs/jsoncpp-1.5.0
    libs/pstreams-0.8.1
)


file(GLOB_RECURSE API_CPPS ../../kernel/API/*.cpp)
file(GLOB_RECURSE DRIVER_CPPS ../../kernel/drivers/*.cpp)


#organized by importance
add_executable(RCServer
    ../main.cpp
    ../RCServer.cpp

    ${API_CPPS}
    ${DRIVER_CPPS}
    ${JSONCPP_CPP}
)

target_link_libraries(RCServer
    #/var/lib/gems/1.9.1/gems/rice-1.7.0/rice/librice.a
    #/var/lib/gems/1.9.1/gems/rice-1.7.0/ruby/lib/lib/librice.a
    pthread
)

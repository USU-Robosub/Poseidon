cmake_minimum_required(VERSION 2.6)

project(PoseidonAPI)

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS "-g -O3 --std=c++11 -Wno-c++98-compat-pedantic -pedantic -Weverything -Wno-unused-parameter -Wno-global-constructors -Wno-exit-time-destructors -Wno-non-virtual-dtor -Wno-weak-vtables -Wno-padded -Wno-cast-align -Wno-gnu -Wno-nested-anon-types -Wno-documentation-unknown-command -Wno-unknown-pragmas")
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS "-g -O3 --std=c++11 -Wall -Wextra -Wdouble-promotion -Wfloat-equal -Wunsafe-loop-optimizations -Wno-unused-parameter")
endif()

include_directories(.)

#organized by importance
add_executable(PoseidonAPI
    main.cpp
    API/ThrustController.cpp
    API/IMUSensor.cpp

    drivers/PWM.cpp
    drivers/I2C.cpp
    drivers/Registry.cpp
)

target_link_libraries(PoseidonAPI pthread)

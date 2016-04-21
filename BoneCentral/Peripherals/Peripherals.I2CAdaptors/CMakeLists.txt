cmake_minimum_required(VERSION 2.8.9)
project(Peripherals.I2CAdaptors)

get_filename_component(Drivers_Path "../../../Drivers/Include" ABSOLUTE)
set(I2CAdaptor_Includes
        "${Drivers_Path}/Interfaces "
        "${Drivers_Path}/Registers "
        "${Drivers_Path}/Sensors "
        "${Drivers_Path}/System "
        "${CMAKE_CURRENT_SOURCE_DIR}/include")
include_directories(${I2CAdaptor_Includes})

file(GLOB_RECURSE ADAPTOR_FILES "src/*.cpp")
add_library(Peripherals.I2CAdaptors SHARED ${ADAPTOR_FILES})
target_link_libraries(Peripherals.I2CAdaptors Drivers Peripherals)
set(I2CAdaptor_Includes ${I2CAdaptor_Includes} PARENT_SCOPE)
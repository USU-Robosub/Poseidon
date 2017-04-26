
cmake_minimum_required(VERSION 2.8.2)
project(catch-download NONE)

include(ExternalProject)

ExternalProject_Add(Catch
        GIT_REPOSITORY https://github.com/philsquared/Catch
        GIT_TAG v1.9.1
        SOURCE_DIR "${CMAKE_BINARY_DIR}/catch-src"
        CONFIGURE_COMMAND ""
        BUILD_COMMAND ""
        INSTALL_COMMAND "")

execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/catch-download)
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/catch-download)

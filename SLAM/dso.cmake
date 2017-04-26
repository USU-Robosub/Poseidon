cmake_minimum_required(VERSION 2.8.2)
project(dso-download NONE)

include(ExternalProject)

ExternalProject_Add(DSO
        GIT_REPOSITORY https://github.com/USU-Robosub/dso
        GIT_TAG master
        SOURCE_DIR "${CMAKE_BINARY_DIR}/dso-src"
        BINARY_DIR "${CMAKE_BINARY_DIR}/dso-bin"
        INSTALL_COMMAND "")
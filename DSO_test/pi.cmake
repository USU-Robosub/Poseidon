set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_VERSION 1)

set(CMAKE_C_COMPILER [path to raspberry pi tool chain repository]/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian/bin/arm-linux-gnueabihf-gcc)
set(CMAKE_CXX_COMPILER [path to raspberry pi tool chain repository]/raspberrypi-tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian/bin/arm-linux-gnueabihf-g++)

set(CMAKE_FIND_ROOT_PATH [path to raspberry pi tool chain repository]/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian)
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

# Todo add -mfpu=neon-vfpv4
set(CMAKE_C_FLAGS "-mcpu=cortex-a7" CACHE STRING "Flags for Raspberry Pi 2")
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS}" CACHE STRING "Flags for Raspberry Pi 2")
# For easier testing with qemu-arm.
set(CMAKE_EXE_LINKER_FLAGS "-static" CACHE STRING "Flags to generate static
executables")

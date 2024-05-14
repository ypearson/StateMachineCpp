# Bare metal build
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSCOR arm)

# Toolchain path
set(TC_PATH $ENV{ARM_PATH})

# Prefix for compiler
set(TC_PREFIX arm-none-eabi-)

# Name for each tool
set(CMAKE_ASM_COMPILER  "${TC_PATH}/${TC_PREFIX}gcc")
set(CMAKE_C_COMPILER    "${TC_PATH}/${TC_PREFIX}gcc")
set(CMAKE_CXX_COMPILER  "${TC_PATH}/${TC_PREFIX}g++")
set(CMAKE_LINKER        "${TC_PATH}/${TC_PREFIX}ld")
set(CMAKE_AR            "${TC_PATH}/${TC_PREFIX}ar")
set(CMAKE_SIZE          "${TC_PATH}/${TC_PREFIX}size")

set(CMAKE_OBJCOPY "${TC_PATH}/${TC_PREFIX}objcopy"
    CACHE FILEPATH "The toolchain objcopy command " FORCE)

set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# Search for the programs in the build host directories
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)

# Generates a compile_commands.json for all compiler calls
# Used in static analysis tools.
set(CMAKE_EXPORT_COMPILE_COMMANDS)

# For libraries and headers in the target directories
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

# CPU flags
set(MCU "-mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb")

set(CMAKE_ASM_FLAGS "-x assembler-with-cpp")

# Set the CMAKE C Flags which should also be used by the assemblers
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${MCU}")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${MCU}")

# Cache the flags for use
set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS}"   CACHE STRING "CFLAGS")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}" CACHE STRING "CXXFLAGS")




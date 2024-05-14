cmake_minimum_required(VERSION 3.16.3)

set(FIRMWARE_VER 1.0.0)

include(build_info.cmake)

project($ENV{TARGET_NAME}_${GIT_BRANCH_NAME}_${GIT_COMMIT_SHA_SHORT}_${BUILD_TIMESTAMP_FILE}
    VERSION 1.0.0
    LANGUAGES CXX C ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

set(EXECUTABLE ${PROJECT_NAME}.elf)

add_compile_definitions(
    DEBUG
    USE_HAL_DRIVER
    STM32F446xx
    LOGGING_ENABLED
)

set(DEV_FLAGS "-Wno-unused-parameter -Wno-unused-variable -Wno-unused-function")
set(WARNING_FLAGS "-Wall -Wextra -Wfatal-errors -Wpedantic -Werror=return-type ${DEV_FLAGS}")
set(COMMON_FLAGS "-fdata-sections -ffunction-sections -fstack-usage -specs=nosys.specs -specs=nano.specs")

# set(DEBUG_FLAGS "-Og -g -gdwarf-2")
# set(RELEASE_FLAGS "-Os")
set(RELEASE_FLAGS "-Ofast -funroll-loops")
set(LTO_FLAG "-flto")

# set(OPTIMIZATION_FLAGS "${DEBUG_FLAGS}")
set(OPTIMIZATION_FLAGS "${RELEASE_FLAGS}")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${WARNING_FLAGS} ${COMMON_FLAGS}")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OPTIMIZATION_FLAGS}")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${WARNING_FLAGS} ${COMMON_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-exceptions -fno-rtti")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OPTIMIZATION_FLAGS}")

set(LINKER_SCRIPT ../STM32F446RETX_FLASH.ld)

set(CMAKE_EXE_LINKER_FLAGS "${LTO_FLAG} ${MCU} -T ${LINKER_SCRIPT} -Wl,-Map=${PROJECT_NAME}.map,--cref -Wl,--gc-sections -Wl,--print-memory-usage")

add_executable(${EXECUTABLE}
    Core/Startup/startup_stm32f446retx.s
    Core/Src/main.c
    Core/Src/stm32f4xx_hal_msp.c
    Core/Src/stm32f4xx_it.c
    Core/Src/syscalls.c
    Core/Src/sysmem.c
    Core/Src/system_stm32f4xx.c
    Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal.c
    Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cortex.c
    Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma.c
    Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma_ex.c
    Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_exti.c
    Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash.c
    Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ex.c
    Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ramfunc.c
    Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_gpio.c
    Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr.c
    Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr_ex.c
    Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc.c
    Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc_ex.c
    Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim.c
    Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim_ex.c
    Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_uart.c 
    App/Src/logging.c
    App/Src/build_information.cpp
    App/Src/application.cpp
    App/Src/Gpio.cpp
    App/Src/Timer.cpp
    App/Src/Led.cpp
    App/Src/uart.cpp
)

target_include_directories(${EXECUTABLE} PRIVATE
    ../
    ./
    Core/Inc 
    Drivers/STM32F4xx_HAL_Driver/Inc 
    Drivers/STM32F4xx_HAL_Driver/Inc/Legacy 
    Drivers/CMSIS/Device/ST/STM32F4xx/Include 
    Drivers/CMSIS/Include 
    App/Inc
)

add_custom_target(
    format
    COMMAND clang-format -i ../*.cpp
    COMMAND clang-format -i ../*.hpp
    COMMENT "Running clang-format on all cpp files"
)

add_custom_command(
    TARGET ${EXECUTABLE} POST_BUILD
    COMMENT "\nGenerating BIN and HEX artifacts from ELF output file."
    COMMAND ${CMAKE_OBJCOPY} -Obinary $<TARGET_FILE:${EXECUTABLE}> ${PROJECT_NAME}.bin
    COMMAND ${CMAKE_OBJCOPY} -Oihex $<TARGET_FILE:${EXECUTABLE}> ${PROJECT_NAME}.hex
)

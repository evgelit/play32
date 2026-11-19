cmake_minimum_required(VERSION 3.20)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# Automatically locate ARM GCC toolchain on PATH (can be overridden via -DCMAKE_TOOLCHAIN_FILE)
if(NOT DEFINED CMAKE_C_COMPILER)
    find_program(ARM_GCC_C NAMES arm-none-eabi-gcc REQUIRED)
    set(CMAKE_C_COMPILER "${ARM_GCC_C}")
endif()

if(NOT DEFINED CMAKE_ASM_COMPILER)
    set(CMAKE_ASM_COMPILER "${CMAKE_C_COMPILER}")
endif()

find_program(ARM_OBJCOPY NAMES arm-none-eabi-objcopy REQUIRED)
find_program(ARM_SIZE    NAMES arm-none-eabi-size)

project(Play32
        VERSION 1.0.0
        DESCRIPTION "Play32 custom HAL framework project"
        LANGUAGES C ASM
)

# Shared Cortex-M4F hardware flags for both compiler and linker
set(MCU_FLAGS
        -mcpu=cortex-m4
        -mthumb
        -mfpu=fpv4-sp-d16
        -mfloat-abi=hard
)

add_executable(${PROJECT_NAME}
        Src/main.c
        Src/play32_startup_stm32f401xx.c
)

set_target_properties(${PROJECT_NAME} PROPERTIES
        SUFFIX ".elf"
)

target_include_directories(${PROJECT_NAME} PRIVATE
        Src/include
)

target_compile_options(${PROJECT_NAME} PRIVATE
        ${MCU_FLAGS}
        -std=c23
        -Wall
        -Wextra
        -Wconversion
        -ffunction-sections
        -fdata-sections
        $<$<CONFIG:Debug>:-O0 -g3>
        $<$<CONFIG:Release>:-O2 -g0>
)

set(LINKER_SCRIPT "${CMAKE_CURRENT_SOURCE_DIR}/STM32F401CCUx_FLASH.ld")

set_target_properties(${PROJECT_NAME} PROPERTIES
        LINK_DEPENDS "${LINKER_SCRIPT}"
)

target_link_options(${PROJECT_NAME} PRIVATE
        ${MCU_FLAGS}
        "-T" "${LINKER_SCRIPT}"
        -nostartfiles
        --specs=nano.specs
        -Wl,-Map=${PROJECT_NAME}.map,--cref
        -Wl,--gc-sections
        -Wl,--print-memory-usage
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${PROJECT_NAME}> ${PROJECT_NAME}.bin
        COMMENT "Generating ${PROJECT_NAME}.bin..."
)

if(ARM_SIZE)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${ARM_SIZE} $<TARGET_FILE:${PROJECT_NAME}>
    )
endif()

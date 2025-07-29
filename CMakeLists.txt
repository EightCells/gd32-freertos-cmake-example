cmake_minimum_required(VERSION 3.20.0)

set(EXEC_NAME "gd32_freertos_template" CACHE STRING "")
set(PROJECT_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}" CACHE STRING "")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_definitions(
    -DGD32F427
)

add_compile_options(
    -mcpu=cortex-m4
    -mfloat-abi=hard
    -mfpu=fpv4-sp-d16
    -specs=nano.specs

    -O0

    -ffunction-sections
    -fdata-sections
    -fstack-usage
    -ffast-math
)

add_link_options(
    -mcpu=cortex-m4
    -mfloat-abi=hard
    -mfpu=fpv4-sp-d16
    -specs=nano.specs
    -static
    -u _printf_float
    -Wl,-Map=${EXEC_NAME}.map
    -Wl,--start-group -lc -lm -Wl,--end-group
    -Wl,--gc-sections
    -T${PROJECT_ROOT_DIR}/gd32f4xx_flash.ld
)

project(GD32-FreeRTOS-Template)

enable_language(C ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(CMAKE_EXECUTABLE_SUFFIX .elf)

# bsp start
set(BSP_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/bsp)

set(BSP_SRC_FILES
    ${BSP_ROOT_DIR}/bsp.c

    ${BSP_ROOT_DIR}/src/gpio.c
    ${BSP_ROOT_DIR}/src/usart.c
    ${BSP_ROOT_DIR}/src/timer.c
    ${BSP_ROOT_DIR}/src/iic.c
)

set(BSP_INC_DIRS
    ${BSP_ROOT_DIR}/
    ${BSP_ROOT_DIR}/inc
)
# bsp end

add_executable(${EXEC_NAME}
    startup_gd32f407_427.s
    user/main.c
    user/gd32f4xx_it.c

    FreeRTOS/FreeRTOS-Plus/FreeRTOS-Plus-CLI/FreeRTOS_CLI.c
    FreeRTOS/FreeRTOS-Plus/FreeRTOS-Plus-CLI/Sample-CLI-commands.c
    FreeRTOS/FreeRTOS-Plus/FreeRTOS-Plus-CLI/UARTCommandConsole.c
    FreeRTOS/FreeRTOS-Plus/FreeRTOS-Plus-CLI/serial.c

    ${BSP_SRC_FILES}
)

target_include_directories(${EXEC_NAME} PUBLIC
    user

    FreeRTOS/FreeRTOS-Plus/FreeRTOS-Plus-CLI

    ${BSP_INC_DIRS}
)

add_subdirectory(${PROJECT_SOURCE_DIR}/firmware firmware)
add_subdirectory(${PROJECT_SOURCE_DIR}/stl stl)
add_subdirectory(${PROJECT_SOURCE_DIR}/FreeRTOS freertos)

# set_property(TARGET freertos_kernel PROPERTY C_STANDARD 90)

target_link_libraries(${EXEC_NAME} gd32f4xx_cmsis gd32f4xx_standard_peripheral user_stl freertos_kernel freertos_config)

add_custom_command(TARGET ${EXEC_NAME}
    POST_BUILD
    COMMAND ${CMAKE_OBJDUMP} -h -S $<TARGET_FILE:${EXEC_NAME}> > $<TARGET_FILE_DIR:${EXEC_NAME}>/${EXEC_NAME}.list
    COMMAND ${CMAKE_OBJCOPY} -O ihex $<TARGET_FILE:${EXEC_NAME}> $<TARGET_FILE_DIR:${EXEC_NAME}>/${EXEC_NAME}.hex
    COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${EXEC_NAME}> $<TARGET_FILE_DIR:${EXEC_NAME}>/${EXEC_NAME}.bin
)

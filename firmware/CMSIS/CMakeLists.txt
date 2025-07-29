add_library(gd32f4xx_cmsis EXCLUDE_FROM_ALL
    GD/GD32F4xx/Source/system_gd32f4xx.c
    GD/GD32F4xx/Source/syscalls.c
)

target_include_directories(gd32f4xx_cmsis PUBLIC
    .
    GD/GD32F4xx/Include
)

target_compile_definitions(gd32f4xx_cmsis PUBLIC -DGD32F427)

target_link_libraries(gd32f4xx_cmsis gd32f4xx_standard_peripheral)

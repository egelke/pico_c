

# Define static library target
add_library(hal STATIC
    egk_sensor.c
)

add_library(hal_pico STATIC
    pico/egk_i2c.c
    pico/egk_time.c
)

# Expose include directory to users of the library
target_include_directories(hal
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/incl
)

target_include_directories(hal_pico
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/incl
)

Target_link_libraries(hal
    egk
)

target_link_libraries(hal_pico
    hardware_i2c 
    pico_stdlib
    egk
)

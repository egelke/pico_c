

# Define static library target
add_library(hal_pico STATIC
    egk_i2c_pico.c
    egk_time_pico.c
)

# Expose include directory to users of the library
target_include_directories(hal_pico
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(hal_pico
    hardware_i2c 
    pico_stdlib
)

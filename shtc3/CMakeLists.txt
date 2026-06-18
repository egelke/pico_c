

# Define OBJECT target
add_library(shtc3 OBJECT
    egk_shtc3.c
)

# Expose include directory to users of the library
target_include_directories(shtc3
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

#target_link_libraries(shtc3
#    hardware_i2c 
#    pico_stdlib
#)

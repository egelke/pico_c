

# Define OBJECT target
add_library(shtc3 OBJECT
    src/egk_shtc3.c
)

# Expose include directory to users of the library
target_include_directories(shtc3
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/incl
)

#target_link_libraries(shtc3
#    PRIVATE hal_pico
#)

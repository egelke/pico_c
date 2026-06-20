

# Define OBJECT target
add_library(sgp4x OBJECT
    src/egk_sgp4x.c
)

# Expose include directory to users of the library
target_include_directories(sgp4x
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/incl
)

target_link_libraries(sgp4x
    egk
    hal
)

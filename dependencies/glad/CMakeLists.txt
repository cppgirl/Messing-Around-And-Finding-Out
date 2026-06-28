add_library(glad INTERFACE
    "${CMAKE_CURRENT_SOURCE_DIR}/src/glad.c"
)

target_include_directories(glad INTERFACE
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

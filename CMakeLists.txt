cmake_minimum_required(VERSION 3.20)

add_subdirectory(dependencies/glfw)
add_subdirectory(dependencies/glad)

project(Jfa)

find_package(OpenGL)

add_executable(Jfa 
    "${CMAKE_SOURCE_DIR}/main.c"
)

target_include_directories(Jfa PUBLIC
    ${OpenGL_INCLUDE_DIRS}
)

target_link_libraries(Jfa PUBLIC 
    glfw
    glad
    ${OpenGL_LIBRARIES}
)

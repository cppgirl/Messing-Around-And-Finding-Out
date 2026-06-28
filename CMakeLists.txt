cmake_minimum_required(VERSION 3.20)

add_subdirectory(dependencies/glfw)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED true)

project(Jfa)

find_package(OpenGL)

add_executable(Jfa 
    "${CMAKE_SOURCE_DIR}/dependencies/glad/src/glad.c"
    "${CMAKE_SOURCE_DIR}/main.c"
)

target_include_directories(Jfa PUBLIC
    ${OpenGL_INCLUDE_DIRS}
    "${CMAKE_SOURCE_DIR}/dependencies/glad/include"
)

target_link_libraries(Jfa PUBLIC 
    glfw
    ${OpenGL_LIBRARIES}
)

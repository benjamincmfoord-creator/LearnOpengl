cmake_minimum_required(VERSION 3.16)

project(OpenGLProject VERSION 1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(glfw3 REQUIRED)

add_executable(OpenGLProject
    src/main.cpp
    src/glad.c
    src/shader.cpp
    src/shader.h
    src/stb_image.h
)

target_include_directories(OpenGLProject PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/includes
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(OpenGLProject PRIVATE
    glfw
    GL
)
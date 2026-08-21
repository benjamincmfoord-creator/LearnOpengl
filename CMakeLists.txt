cmake_minimum_required(VERSION 3.16)

project(OpenGLProject VERSION 1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find GLFW installed on the system
find_package(glfw3 REQUIRED)

# Create executable
add_executable(OpenGLProject
    src/main.cpp
    src/glad.c
)

# Tell the compiler where to find GLAD headers
target_include_directories(OpenGLProject PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Link GLFW and OpenGL
target_link_libraries(OpenGLProject PRIVATE
    glfw
    GL
)
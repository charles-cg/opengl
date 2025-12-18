cmake_minimum_required(VERSION 4.0.0)
project(hello_window VERSION 1.0.0)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

add_executable(hello_window 
    src/glad.c
    src/main.cpp
    src/shaderClass.cpp
    src/VAO.cpp
    src/VBO.cpp
    src/EBO.cpp
)

target_include_directories(hello_window PRIVATE dependencies)

target_link_libraries(hello_window glfw OpenGL::GL)

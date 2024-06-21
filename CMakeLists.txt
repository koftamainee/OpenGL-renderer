cmake_minimum_required(VERSION 3.5)
project(OpenGL-renderer VERSION 0.1.0 LANGUAGES C CXX)

add_executable(OpenGL-renderer src/main.cpp libs/glad/glad.h libs/glad/glad.c)

target_link_libraries(OpenGL-renderer glfw)

add_compile_options(OpenGL-renderer pthead)
cmake_minimum_required(VERSION 3.10)
project(OpenGL_renderer VERSION 0.1.0 LANGUAGES C CXX)

add_executable(OpenGL_renderer src/main.cpp libs/glad/glad.h libs/glad/glad.c)

target_link_libraries(OpenGL_renderer glfw)

add_compile_options(OpenGL_renderer pthead)
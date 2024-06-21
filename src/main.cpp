#include <filesystem>
#include <iostream>
#include <fstream>
#include "../libs/glad/glad.h"
#include <GLFW/glfw3.h>


std::string read_file(const std::filesystem::path& path) {

    std::ifstream in(path, std::ios::binary);
    const auto sz = std::filesystem::file_size(path);
    std::string result(sz, '\0');
    in.read(result.data(), sz);
    return result;

}


unsigned int compile_shader(unsigned int shaderType, const std::string& src) {

    unsigned id = glCreateShader(shaderType);
    const char* raw = src.c_str();
    glShaderSource(id, 1, &raw, nullptr);
    glCompileShader(id);
    return id;

}


unsigned int create_shader(const std::string& vertex, const std::string& fragment) {

    unsigned vs = compile_shader(GL_VERTEX_SHADER, vertex);
    unsigned fs = compile_shader(GL_FRAGMENT_SHADER, fragment);

    unsigned program = glCreateProgram();
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);

    glValidateProgram(program);
    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;

}


void framebuffer_size_callback(GLFWwindow* window, int width, int height) {

    glViewport(0, 0, width, height);

}


int main(void) {
    
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1080, 720, "Hello World", NULL, NULL);
    if (!window) {

        glfwTerminate();
        return -1;

    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Init GLAD */
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {

        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;

    }

    /* Create shaders */
    float vertices[] = {
        -1.0f, -1.0f,
        1.0f, -1.0f,
        1.0f, 1.0f,

        1.0f, 1.0f,
        -1.0f, 1.0f,
        -1.0f, -1.0f
    };

    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
    glEnableVertexAttribArray(0);

    std::string vertex = read_file("shaders/vertex.shader");
    std::string fragment = read_file("shaders/fragment.shader");
    unsigned int shader = create_shader(vertex, fragment);
    glUseProgram(shader);

    /* Set the viewport */
    glViewport(0, 0, 1080, 720);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    /* Uniforms */
    int resolution_location = glGetUniformLocation(shader, "resolution");
    int time_location = glGetUniformLocation(shader, "time");

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {

        /* Render */
        float time_value = static_cast<float>(glfwGetTime());

        glUniform2f(resolution_location, 1080.0f, 720.0f);
        glUniform1f(time_location, time_value);

        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 6);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();

    }

    glDeleteProgram(shader);
    glfwTerminate();
    return 0;
    
}

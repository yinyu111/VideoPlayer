//
// Created by 尹玉 on 2024/5/10.
//

#include "Render.h"
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

int test::testMain() {
    std::cout << "testMain()" << std::endl;

    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    int width = 1280;
    int height = 720;
    GLFWwindow* window = glfwCreateWindow(width, height, "VideoPlayer", NULL, NULL);
    glfwMakeContextCurrent(window);

    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);

    char* str = "int main";
//    RenderShader* shader = new RenderShader(str, RenderShaderType::RENDER_VERTEX_SHADER);
    RenderProgram* program = new RenderProgram(str, str);

    while (!glfwWindowShouldClose(window)) {
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

//    delete shader;
    delete program;

    glfwTerminate();
    std::cout << "Hello, videoPlayer!kaku2" << std::endl;

    return 0;
}
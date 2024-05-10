//
// Created by 尹玉 on 2024/5/10.
//

#include "test.h"
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

    while (!glfwWindowShouldClose(window)) {
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    std::cout << "Hello, videoPlayer!kaku2" << std::endl;

    return 0;
}
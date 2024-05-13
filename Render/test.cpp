//
// Created by 尹玉 on 2024/5/10.
//

#include "Render.h"
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define SHADER1(x) #x
#define CHANGE(shader) "" SHADER1(shader)


#define STRINGIZE(x)  #x
#define SHADER(shader) "" STRINGIZE(shader)




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

    char* vertexShaderStr =
            "#version 330 core\n"
            "layout (location = 0) in vec3 pos;\n"
            "out vec3 outPos;"
            "void main()\n"
            "{\n"
            "   outPos = pos;\n"
            "   gl_Position = vec4(pos, 1.0);\n"
            "}\n";

    char* fragmentShaderStr =
            "#version 330 core\n"
            "in vec3 outPos;\n"
            "out vec4 rgbaColor;\n"
            "void main() {\n"
            "    rgbaColor = vec4(outPos, 1.0);\n"
            "}\n";

//    char* vertexShaderStr = SHADER
//    (
//            #version 330 core
//            layout (location = 0) in vec3 pos;
//            out vec3 outPos;
//            void main() {
//                outPos = pos
//                gl_position = position;
//            }
//    );
//
//    char* fragmentShaderStr = SHADER
//    (
//            #version 330 core\n
//            in vec3 outPos;
//            out vec4 rgbaColor;
//            void main() {
//                rgbaColor = vec4(outPos, 1.0);
//            }
//    );

    std::cout << "vertexShaderStr:" << std::endl;
    std::cout << vertexShaderStr << std::endl;
    std::cout << "fragmentShaderStr:" << std::endl;
    std::cout << fragmentShaderStr << std::endl;

    float vertex[] = {
            0.0f, 1.0f, 0.0,
            1.0f, -1.0f, 1.0,
            -1.0f, -1.0f, 0.0,
    };
    RenderVAO* vao = new RenderVAO();
    vao->importVertex3D(vertex, 3, 0);

//    RenderShader* shader = new RenderShader(str, RenderShaderType::RENDER_VERTEX_SHADER);
    RenderProgram* program = new RenderProgram(vertexShaderStr, fragmentShaderStr);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        program->useProgram();
        vao->bindVAO();

        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

//    delete shader;
    delete vao;
    delete program;

    glfwTerminate();
    std::cout << "Hello, videoPlayer!kaku2" << std::endl;

    return 0;
}
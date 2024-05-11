//
// Created by 尹玉 on 2024/5/10.
//

#ifndef VIDEOPLAYER_TEST_H
#define VIDEOPLAYER_TEST_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

enum RenderShaderType{
    RENDER_VERTEX_SHADER = 1,
    RENDER_FRAGMENT_SHADER,
};

class RenderShader {
public:
    RenderShader(char* shaderStr, RenderShaderType type);
    ~RenderShader();

public:
    GLuint shader = 0;
};

class RenderProgram {
public:
    RenderProgram(char* vertexShaderStr, char* fragmentShaderStr);
    ~RenderProgram();

public:
    GLuint program = 0;
};


class test {
public:
    static int testMain();
};


#endif //VIDEOPLAYER_TEST_H

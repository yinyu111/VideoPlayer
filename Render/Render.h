//
// Created by 尹玉 on 2024/5/10.
//

#ifndef VIDEOPLAYER_TEST_H
#define VIDEOPLAYER_TEST_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>

enum RenderShaderType{
    RENDER_VERTEX_SHADER = 1,
    RENDER_FRAGMENT_SHADER = 2,
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

    int useProgram();
public:
    GLuint program = 0;
};

class RenderVAO{
public:
    RenderVAO();
    ~RenderVAO();

    int importVertex3D(float* vertexData, int dataNum, int layout);
    int setEBOIndex(unsigned int* rboData, int dataNum);
    int bindVAO();
    int Draw();

public:
    GLuint vao = 0;
    GLuint ebo = 0;
    std::vector<GLuint> vboList;
    GLuint drawTime = 0;
};


class test {
public:
    static int testMain();
};


#endif //VIDEOPLAYER_TEST_H

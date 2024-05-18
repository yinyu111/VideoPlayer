//
// Created by 尹玉 on 2024/5/17.
//

#include "Render.h"

char* vertexShaderStr =
        "#version 330 core\n"
        "layout (location = 0) in vec3 pos;\n"
        "layout (location = 1) in vec3 uvPos;\n"
        "uniform float a;"
        "out vec3 outPos;"
        "out vec3 outuvPos;"
        "void main()\n"
        "{\n"
        "   outPos = pos;\n"
        "   outuvPos = uvPos;\n"
        "   gl_Position = vec4(pos.x * a, pos.y * a, pos.z * a, 1.0);\n"
        "}\n";

char* fragmentShaderStr =
        "#version 330 core\n"
        "uniform sampler2D t;"
        "in vec3 outPos;\n"
        "in vec3 outuvPos;\n"
        "out vec4 rgbaColor;\n"
        "void main() {\n"
        //            "    //纹理坐标"
        "    vec2 uv = vec2(outuvPos.x, outuvPos.y);\n"
        //            "    vec2 uv = vec2(1.0, 0.0);"
        "    vec4 color = texture(t, uv);\n"
        "    rgbaColor = vec4(outPos, 1.0);\n"
        "    rgbaColor = color;\n"
        "}\n";

float vertex[] = {
        -1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        1.0f, -1.0f, 1.0f,
        -1.0f, -1.0f, 0.0f,
};

float textureUV[] = {
        0.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f,
};

unsigned int eboIndex[] = {
        0, 1, 3,
        1, 2, 3,
};

unsigned char imageData[] = {
        255, 0, 0,
        0, 255, 0,
        0, 0, 255,
        0, 0, 0,
};

RenderThread::RenderThread(int _renderWidth, int _renderheight) {
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(renderWidth, renderheight, "VideoPlayer", NULL, NULL);
    glfwMakeContextCurrent(window);

    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);

    vao = new RenderVAO();
    vao->importVertex3D(vertex, 4, 0);
    vao->importVertex3D(textureUV, 4, 1);
    vao->setEBOIndex(eboIndex, 6);

    program = new RenderProgram(vertexShaderStr, fragmentShaderStr);

    textureIndex = 0;
    renderWidth = _renderWidth;
    renderheight = _renderheight;
}

RenderThread::~RenderThread() {
    delete vao;
    delete program;

    glDeleteTextures(1, &textureIndex);

    glfwTerminate();
}

void RenderThread::run() {
    //生成纹理对象
    glGenTextures(1, &textureIndex);
    //绑定纹理对象
    glBindTexture(GL_TEXTURE_2D, textureIndex);

    //GL_LINEAR? GL_REPEAT? GL_CLAMP_TO_EDGE?
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    //设置纹理参数
    //GL_NEAREST？GL_REPEAT？
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //设置一字节对齐
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    //分配纹理内存
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, renderWidth, renderheight, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);

    float a = 0;
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);


        float _a = sin(a);
        _a = 1;
        a += 0.1;

        // 获取uniform变量的位置
        GLint timeLocation = glGetUniformLocation(program->program, "a");
        glUniform1f(timeLocation, _a);

//        GLint texture = glGetUniformLocation(program->program, "t");
//        glUniform1f(texture, 0);// 0表示第一个纹理单元
//        glBindTexture(GL_TEXTURE_2D, texture); // 绑定纹理

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureIndex); // 绑定纹理
        GLint texture = glGetUniformLocation(program->program, "t");
        glUniform1i(texture, 0);// 0表示第一个纹理单元


        program->useProgram();

        vao->Draw();
//        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}
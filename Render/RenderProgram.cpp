//
// Created by 尹玉 on 2024/5/11.
//

#include "Render.h"

RenderProgram::RenderProgram(char* vertexShaderStr, char* fragmentShaderStr) {
    program = glCreateProgram();

    RenderShader vertexShader(vertexShaderStr, RenderShaderType::RENDER_VERTEX_SHADER);
    RenderShader fragmentShader(fragmentShaderStr, RenderShaderType::RENDER_FRAGMENT_SHADER);

    glAttachShader(program, vertexShader.shader);
    glAttachShader(program, fragmentShader.shader);

    glLinkProgram(program);

    GLint status;
    glGetProgramiv(program, GL_LINK_STATUS, &status);

    if (status == GL_TRUE) {

    } else {
        GLint length;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
        GLchar* log = (GLchar*)malloc(length);
        glGetProgramInfoLog(program, length, &length, log);
        std::cerr << "Vertex shader compilation error:" << log << std::endl;
        free(log);
    };
}

RenderProgram::~RenderProgram() {
    if (program != 0) {
        glDeleteProgram(program);
        program = 0;
    }
}

int RenderProgram::useProgram() {
    glUseProgram(program);
    return 0;
}
//
// Created by 尹玉 on 2024/5/11.
//

#include "Render.h"

RenderShader::RenderShader(char* shaderStr, RenderShaderType type) {
    if (type == RenderShaderType::RENDER_VERTEX_SHADER) {
        shader = glCreateShader(GL_VERTEX_SHADER);
    }
    else if (type == RenderShaderType::RENDER_FRAGMENT_SHADER) {
        shader = glCreateShader(GL_FRAGMENT_SHADER);
    }

    glShaderSource(shader, 1, &shaderStr, NULL);

    glCompileShader(shader);

    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

    if (status == GL_TRUE) {

    } else {
        GLint length;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
        GLchar* log = (GLchar*)malloc(length);
        glGetShaderInfoLog(shader, length, &length, log);
        std::cerr << "Vertex shader compilation error:" << log << std::endl;
        free(log);
    };
}

RenderShader::~RenderShader() {
    if (shader != 0) {
        glDeleteShader(shader);
    }
}
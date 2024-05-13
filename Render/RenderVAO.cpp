//
// Created by 尹玉 on 2024/5/13.
//
#include "Render.h"

RenderVAO::RenderVAO() {
    glGenVertexArrays(1, &vao);
}

RenderVAO::~RenderVAO() {
//    for (auto i: vboList) {
//        glDeleteBuffers(1, &i);
//    }
//    vboList.clear();
    for (int i = 0; i < vboList.size();i++) {
        GLuint vbo = vboList[i];
        glDeleteBuffers(1, &vbo);
    }
    vboList.clear();

    if (vao != 0) {
        glDeleteVertexArrays(1, &vao);
        vao = 0;
    }
}

int RenderVAO::importVertex3D(float* vertexData, int num, int layout) {
    glBindVertexArray(vao);

    GLuint vbo = 0;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * num, vertexData, GL_STATIC_DRAW);

    glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (GLvoid*)0);
    glEnableVertexAttribArray(layout);

    vboList.push_back(vbo);

    glBindVertexArray(0);
    return 0;
}

int RenderVAO::bindVAO() {
    if (vao == 0) {
        return -1;
    }

    glBindVertexArray(vao);
    return 0;
}
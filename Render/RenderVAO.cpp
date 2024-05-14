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

    if (ebo != 0) {
        glDeleteBuffers(1, &ebo);
        ebo = 0;
    }
    if (vao != 0) {
        glDeleteVertexArrays(1, &vao);
        vao = 0;
    }
}

int RenderVAO::importVertex3D(float* vertexData, int dataNum, int layout) {
    glBindVertexArray(vao);

    GLuint vbo = 0;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * dataNum, vertexData, GL_STATIC_DRAW);

//    layout：这是顶点属性的位置索引，通常从0开始。
//    3：这表示每个顶点属性包含3个单精度浮点数（GL_FLOAT）。
//    GL_FLOAT：这是顶点属性数据的类型。
//    GL_FALSE：这表示顶点属性不会被标准化。
//    3 * sizeof(float)：这是顶点属性数据的步长，即相邻顶点属性之间的偏移量。在这个例子中，每个顶点属性占用3个浮点数的空间，所以步长是3 * sizeof(float)。
//    (GLvoid*)0：这是顶点属性数据的偏移量，即从顶点数据缓冲区开始到第一个顶点属性数据之间的字节偏移量。在这里，偏移量设置为0，意味着顶点属性数据直接紧跟在顶点数据之后。

    //设置顶点属性的数据布局。这个函数定义了如何从顶点缓冲区中读取顶点属性数据，以及这些数据的类型、大小、步长和偏移量。
    glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (GLvoid*)0);
    //用于启用一个顶点属性，以便OpenGL可以在渲染时使用它。
    glEnableVertexAttribArray(layout);

    vboList.push_back(vbo);

    glBindVertexArray(0);
    return 0;
}

int RenderVAO::setEBOIndex(unsigned int* rboData, int dataNum) {
    glBindVertexArray(vao);

    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    //设置数据
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * dataNum, rboData, GL_STATIC_DRAW);

    drawTime = dataNum;

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

int RenderVAO::Draw() {
    //绑定vao
    bindVAO();

    glDrawElements(GL_TRIANGLES, drawTime, GL_UNSIGNED_INT, 0);
    return 0;
}
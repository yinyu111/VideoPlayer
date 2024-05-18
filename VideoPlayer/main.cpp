//
// Created by 尹玉 on 2024/4/21.
//

#include <thread>
#include <iostream>
#include "AVPlayer/AVPlayer.h"
#include "AVReader/AVManager.h"
#include "Render/Render.h"


//int main5() {
//    RenderThread* renderThread = new RenderThread(2, 2);
//    renderThread->Start();
//
//    AVPlayer* avPlayer = new AVPlayer("/Users/yinyu/code/testVideo/mumu.mp4");
//
//    avPlayer->Open(0);
//    avPlayer->Play();
//
////     std::this_thread::sleep_for(std::chrono::seconds(20));
//
//    std::this_thread::sleep_for(std::chrono::seconds(5));
//
//    avPlayer->Pause();
//
//    std::cout << "=================Pause====================" << std::endl;
//
//    std::this_thread::sleep_for(std::chrono::seconds(2));
//
//    avPlayer->Play();
//
//    std::this_thread::sleep_for(std::chrono::seconds(2));
//
//    avPlayer->Stop();
//
//    std::cout << "=================Stop====================" << std::endl;
//
//    std::this_thread::sleep_for(std::chrono::seconds(2));
//
////    avPlayer->Seek(2);
////
////     std::cout << "=================Seek====================" << std::endl;
////
////     std::this_thread::sleep_for(std::chrono::seconds(20));
//
//    return 0;
//}


int main() {
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

    char* fragmentShaderStr1 =
            "#version 330 core\n"
            "uniform sampler2D textureY;"
            "uniform sampler2D textureU;"
            "uniform sampler2D textureV;"
            "in vec3 outPos;\n"
            "in vec3 outuvPos;\n"
            "out vec4 rgbaColor;\n"
            "void main() {\n"
            "    vec2 uv = vec2(outuvPos.x, outuvPos.y);\n"
            "    float y = texture(textureY, uv).r;\n"
            "    float u = texture(textureU, uv).r - 0.5;\n"
            "    float v = texture(textureV, uv).r - 0.5;\n"
            "    float r = y + 1.402 * v;\n"
            "    float g = y - 0.344136 * u - 0.714136 * v;\n"
            "    float b = y + 1.772 * u;\n"
            "    rgbaColor = vec4(r, g, b, 1.0);\n"
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
            -1.0f, -1.0f, 0.0f,
            1.0f, -1.0f, 0.0f,
            1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f, 0.0f,
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
    float a = 0;

    RenderVAO* vao = new RenderVAO();
    vao->importVertex3D(vertex, 4, 0);
    vao->importVertex3D(textureUV, 4, 1);
    vao->setEBOIndex(eboIndex, 6);

//    RenderShader* shader = new RenderShader(str, RenderShaderType::RENDER_VERTEX_SHADER);
    RenderProgram* program = new RenderProgram(vertexShaderStr, fragmentShaderStr);

    int w = 1280;
    int h = 720;
    unsigned char imageData[] = {
            255, 0, 0,
            0, 255, 0,
            0, 0, 255,
            0, 0, 0,
    };
//    unsigned char imageData[] = {
//            0, 0, 255,
//            0, 0, 255,
//            0, 0, 255,
//            0, 0, 255,
//    };
    //生成纹理对象
    GLuint textureIndex = 0;
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
//    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 2, 2, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
//    glFramebufferTexture2D();
//    glFramebufferTexture();



    AVPlayer* avPlayer = new AVPlayer("/Users/yinyu/code/testVideo/mumu.mp4");

    avPlayer->Open(0);
    avPlayer->Play();

    AVRGBData* rgb = new AVRGBData(width, height);

    while (!glfwWindowShouldClose(window)) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));

        if (avPlayer->syncThread->renderQueue.GetSize() > 0) {
            avPlayer->syncThread->renderQueue.Pop(&rgb);
        }
        if (rgb->rgbData != nullptr) {
            std::cout << "render videoFrame! PTSTime:" << rgb->pts <<std::endl;

//            int lineSize = renderFrame->GetLineSize0();
//            unsigned char* data0 = new unsigned char[lineSize];
//            renderFrame->GetData0(data0);


            // 更新纹理数据
            glBindTexture(GL_TEXTURE_2D, textureIndex);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, rgb->rgbData);
//            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);

            // 解绑纹理
            glBindTexture(GL_TEXTURE_2D, 0);

            //可能会内存泄漏 之后看下
//            delete renderFrame;
            rgb->rgbData = nullptr;

            if (rgb->isEOF) {
                break;
            }
        }
        else {
            continue;
        }

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

//    delete shader;
    delete vao;
    delete program;

    // 在渲染循环结束后删除资源
    glDeleteTextures(1, &textureIndex);

    glfwTerminate();
    std::cout << "Hello, videoPlayer!kaku2" << std::endl;

    return 0;
}

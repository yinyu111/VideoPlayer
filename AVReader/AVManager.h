//
// Created by 尹玉 on 2024/4/10.
//

#ifndef VIDEOPLAYER_AVMANAGER_H
#define VIDEOPLAYER_AVMANAGER_H

extern "C" {
    #include <libavformat/avformat.h>
    #include <libavformat/avio.h>
    #include <libavformat/version_major.h>
    #include <libavformat/version.h>
    #include <libavcodec/avcodec.h>
    #include <libavcodec/codec_par.h>
    #include <libavutil/pixdesc.h>
};

#include "AVHeader.h"

class AVPacketManager
{
public:
    AVPacket* avPacket = nullptr;
};

class AVFrameManager
{
public:
    AVFrame* avFrame = nullptr;
    double ptsSec = 0.0;
};

class AVRGBData
{
public:
    unsigned char* rgbData;
    int width;
    int heigth;
    long long pts;
    bool isEOF;

    AVRGBData(int w, int h) : width(w), heigth(h) {
        // 计算所需内存大小
        int size = width * heigth * 3; // 假设每个像素是 3 字节（RGB）

        // 动态分配内存
        rgbData = new unsigned char[size];

        pts = -1;
        isEOF = false;
    }

    // 析构函数
    ~AVRGBData() {
        // 释放内存
        delete[] rgbData;
    }
};

class AVFormatManager
{
public:
    AVFormatContext* formatCtx = nullptr;
};

class AVStreamManager
{
public:
    AVCodecParameters* codecPar = nullptr;
};

class AVDecoderManager
{
public:
    AVCodecContext* codecCtx = nullptr;
};

#endif //VIDEOPLAYER_AVMANAGER_H

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

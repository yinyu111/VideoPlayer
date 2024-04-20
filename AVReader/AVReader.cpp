//
// Created by 尹玉 on 2024/4/9.
//

#include "AVReader.h"
#include "AVManager.h"

AVReader::AVReader() {
    avFormatManager = new AVFormatManager();
    avFormatManager->formatCtx = avformat_alloc_context();
}

AVReader::~AVReader() {
    if (avFormatManager->formatCtx != nullptr) {
        avformat_free_context(avFormatManager->formatCtx);
        avFormatManager->formatCtx = nullptr;
    }

    if (avFormatManager != nullptr) {
        delete avFormatManager;
        avFormatManager = nullptr;
    }
}

int AVReader::GetStreamCount() {
    if (avFormatManager != nullptr) {
        return avFormatManager->formatCtx->nb_streams;
    }
    return -1;
}

int AVReader::GetStream(AVReaderStream* readerStream, int streamID) {
    int streamCount = GetStreamCount();
    if (streamID > streamCount) {
        std::cout << "AVReader::GetStream error!" << std::endl;
        return -1;
    }

    AVStream* avStream = avFormatManager->formatCtx->streams[streamID];

    readerStream->streamIndex = avStream->index;
    int ret = avcodec_parameters_copy(readerStream->avStreamManager->codecPar, avStream->codecpar);
    if (ret < 0) {
        std::cout << "AVReader::GetStream parameters_copy error!" << std::endl;
        return -1;
    }

    return 0;
}

int AVReader::GetVideoStreamIndex() {
    return av_find_best_stream(avFormatManager->formatCtx, AVMediaType::AVMEDIA_TYPE_VIDEO, -1, -1, NULL, NULL);
}
int AVReader::GetAudioStreamIndex() {
    return av_find_best_stream(avFormatManager->formatCtx, AVMediaType::AVMEDIA_TYPE_AUDIO, -1, -1, NULL, NULL);
}

int AVReader::Open(const char* sourcePath) {
    if (avFormatManager->formatCtx == nullptr) {
        std::cout << "AVReader::Open formatCtx is nullptr!" << std::endl;
        return -1;
    }
    int ret = avformat_open_input(&avFormatManager->formatCtx, sourcePath, nullptr, nullptr);

    if (!ret) {
        avformat_find_stream_info(avFormatManager->formatCtx, nullptr);
    }
    return ret;
}

int AVReader::Close() {
    if (avFormatManager->formatCtx == nullptr) {
        std::cout << "AVReader::Open formatCtx is nullptr!" << std::endl;
        return -1;
    }

    avformat_close_input(&avFormatManager->formatCtx);
    return 0;
}

int AVReader::Read(AVReaderPacket* packet) {
    if (avFormatManager->formatCtx == nullptr) {
        std::cout << "AVReader::Open formatCtx is nullptr!" << std::endl;
        return -1;
    }

    int ret = av_read_frame(avFormatManager->formatCtx, packet->avPacketManager->avPacket);
    return ret;
}
//
// Created by 尹玉 on 2024/4/17.
//

#include "AVReader.h"
#include "AVManager.h"

AVDecoder::AVDecoder() {
    avDecoderManager = new AVDecoderManager();
    avDecoderManager->codecCtx = avcodec_alloc_context3(nullptr);
}

AVDecoder::~AVDecoder() {
    if (avDecoderManager->codecCtx != nullptr) {
        avcodec_free_context(&avDecoderManager->codecCtx);
        avDecoderManager->codecCtx = nullptr;
    }

    if (avDecoderManager != nullptr) {
        delete avDecoderManager;
        avDecoderManager = nullptr;
    }
}

int AVDecoder::Init(AVReaderStream* stream) {
    timebaseNum = stream->timebaseNum;
    timebaseDen = stream->timebaseDen;
    duration = stream->duration;

    avcodec_parameters_to_context(avDecoderManager->codecCtx, stream->avStreamManager->codecPar);
    const AVCodec* avCodec = avcodec_find_decoder(avDecoderManager->codecCtx->codec_id);
    int ret = avcodec_open2(avDecoderManager->codecCtx, avCodec, nullptr);
    if (ret) {
        std::cout << "AVDecoder::Init avcodec_open2 failed" << std::endl;
    }

    return ret;
}

int AVDecoder::SendPacket(AVReaderPacket* packet) {
    int ret;
    if (packet != nullptr) {
        ret = avcodec_send_packet(avDecoderManager->codecCtx, packet->avPacketManager->avPacket);
    }
    else {
        ret = avcodec_send_packet(avDecoderManager->codecCtx, nullptr);
    }
    return ret;
}

int AVDecoder::RecvFrame(AVReaderFrame** frame) {
    int ret = avcodec_receive_frame(avDecoderManager->codecCtx, (*frame)->avFrameManager->avFrame);
    if (!ret) {
        //计算秒级时间戳
        (*frame)->avFrameManager->ptsSec = (*frame)->avFrameManager->avFrame->pts * 1.0 * timebaseNum / timebaseDen;
        (*frame)->durationSec = duration* 1.0 * timebaseNum / timebaseDen;
    }
    return ret;
}

int AVDecoder::Close() {
    avcodec_close(avDecoderManager->codecCtx);
    return 0;
}
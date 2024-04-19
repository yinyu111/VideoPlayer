//
// Created by 尹玉 on 2024/4/10.
//

#include "AVReader.h"
#include "AVManager.h"

AVReaderPacket::AVReaderPacket() {
    avPacketManager = new AVPacketManager();
    avPacketManager->avPacket = av_packet_alloc();
}

AVReaderPacket::~AVReaderPacket() {
    if (avPacketManager->avPacket != nullptr) {
        av_packet_free(&avPacketManager->avPacket);
        avPacketManager->avPacket = nullptr;
    }

    if (avPacketManager != nullptr) {
        delete avPacketManager;
        avPacketManager = nullptr;
    }
}

int AVReaderPacket::GetIndex() {
    return avPacketManager->avPacket->stream_index;
}
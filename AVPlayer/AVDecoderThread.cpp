//
// Created by 尹玉 on 2024/4/23.
//

#include "AVPlayer.h"
#include <thread>

AVDecoderThread::AVDecoderThread() {
    decoder = new AVDecoder();
}

AVDecoderThread::~AVDecoderThread() {
    if (decoder != nullptr) {
        delete decoder;
        decoder = nullptr;
    }
}

int AVDecoderThread::Init(AVReaderStream* readerStream) {
    return decoder->Init(readerStream);
}

int AVDecoderThread::PutPacket(AVReaderPacket* readerPacket) {
    packetQueue.Push(readerPacket);
    return 0;
}

int AVDecoderThread::GetPacketQueueSize() {
    return packetQueue.GetSize();
}

void AVDecoderThread::run() {
    int frameCount = 0;
    while (!stopFlag) {
        AVReaderPacket* readerPacket = nullptr;
        int i = packetQueue.GetSize();
        int ret = packetQueue.Pop(&readerPacket);
        if (ret) {
//            std::cout << "AVDecoderThread::packetQueue.Pop failed!" << std::endl;
            continue;
        }

        decoder->SendPacket(readerPacket);
        while (1) {
            AVReaderFrame* recvFrame = new AVReaderFrame();
            ret = decoder->RecvFrame(&recvFrame);
            if (ret) {
                break;
            }

            frameCount++;
            std::cout << "recv frame success! frameCount:" << frameCount << std::endl;

            std::this_thread::sleep_for(std::chrono::seconds(1));
        }

    }
}

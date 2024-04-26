//
// Created by 尹玉 on 2024/4/23.
//

#include "AVPlayer.h"
#include <thread>

AVDecoderThread::AVDecoderThread(AVSyncThread* _synvThread) {
    decoder = new AVDecoder();
    synvThread = _synvThread;
}

AVDecoderThread::~AVDecoderThread() {
    if (decoder != nullptr) {
        delete decoder;
        decoder = nullptr;
    }
}

int AVDecoderThread::Init(AVReaderStream* readerStream, DecoderType _decoderType) {
    decoderType = _decoderType;
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
        std::this_thread::sleep_for(std::chrono::milliseconds(1));

        if (decoderType == DECODER_TYPE_VIDEO) {
            if (synvThread->GetVideoQueueSize() > 10) {
                continue;
            }
        }
        if (decoderType == DECODER_TYPE_AUDIO) {
            if (synvThread->GetAudioQueueSize() > 10) {
                continue;
            }
        }



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

            if (synvThread != nullptr && decoderType == DECODER_TYPE_VIDEO) {
                synvThread->PushFrameToVideoQueue(recvFrame);
            }
            if (synvThread != nullptr && decoderType == DECODER_TYPE_AUDIO) {
                synvThread->PushFrameToAudioQueue(recvFrame);
            }
//            std::cout << "recv frame success! frameCount:" << frameCount << std::endl;
//            std::this_thread::sleep_for(std::chrono::seconds(1));
        }

    }
}

//
// Created by 尹玉 on 2024/4/22.
//

#include "AVPlayer.h"

AVReaderThread::AVReaderThread(std::string _sourcePath, AVSyncThread* _synvThread) {
    sourcePath = _sourcePath;
    synvThread = _synvThread;
}
AVReaderThread::~AVReaderThread() {

}

void AVReaderThread::run() {
    AVReader reader;
    int ret = reader.Open(sourcePath.c_str());
    if (ret) {
        std::cout << "open file failed!" << std::endl;
        std::cout << "ret: " << ret << std::endl;
        return;
    }


    int videoStreamIndex = reader.GetVideoStreamIndex();
    int audioStreamIndex = reader.GetAudioStreamIndex();


    AVDecoderThread* videoDecoderThread = new AVDecoderThread(synvThread);
    AVDecoderThread* audioDecoderThread = new AVDecoderThread(synvThread);

    AVReaderStream videoStream;
    reader.GetStream(&videoStream, videoStreamIndex);
    videoDecoderThread->Init(&videoStream, DecoderType::DECODER_TYPE_VIDEO);

    AVReaderStream audioStream;
    reader.GetStream(&audioStream, audioStreamIndex);
    audioDecoderThread->Init(&audioStream, DecoderType::DECODER_TYPE_AUDIO);

    videoDecoderThread->Start();
    audioDecoderThread->Start();

    while (!stopFlag) {
        if (videoDecoderThread->GetPacketQueueSize() > 5 && audioDecoderThread->GetPacketQueueSize() > 5) {
            continue;
        }

        AVReaderPacket* packet = new AVReaderPacket();
        ret = reader.Read(packet);
        if (ret) {
            std::cout << "read frame failed!" << std::endl;
            delete packet;
            break;
        }

//        std::cout << "read frame success! i:" << i << std::endl;
        int streamIndex = packet->GetIndex();
        if (streamIndex == videoStreamIndex) {
            videoDecoderThread->PutPacket(packet);
//            std::cout << "VideoPacketQueueSize: " << videoDecoderThread->GetPacketQueueSize() << std::endl;
        }
        if (streamIndex == audioStreamIndex) {
            audioDecoderThread->PutPacket(packet);
//            std::cout << "AudioPacketQueueSize: " << audioDecoderThread->GetPacketQueueSize() << std::endl;
        }
//        std::cout << "put packet success! i:" << i << std::endl;
//        delete packet;
    }

    videoDecoderThread->Stop();
    audioDecoderThread->Stop();

    reader.Close();
}
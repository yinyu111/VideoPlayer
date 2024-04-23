//
// Created by 尹玉 on 2024/4/22.
//

#include "AVPlayer.h"

AVReaderThread::AVReaderThread(std::string _sourcePath) {
    sourcePath = _sourcePath;
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



    int i = 100;
    int videoStreamIndex = reader.GetVideoStreamIndex();
    int audioStreamIndex = reader.GetAudioStreamIndex();

    while (i) {
        AVReaderPacket* packet = new AVReaderPacket();
        ret = reader.Read(packet);
        if (ret) {
            std::cout << "read frame failed! i:" << i << std::endl;
            delete packet;
            break;
        }

        std::cout << "read frame success! i:" << i << std::endl;

        delete packet;
        i--;
    }

    reader.Close();
}
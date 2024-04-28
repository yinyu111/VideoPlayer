//
// Created by 尹玉 on 2024/4/21.
//

#include "AVPlayer.h"

AVPlayer::AVPlayer(std::string _sourcePath) {
    sourcePath = _sourcePath;
}
AVPlayer::~AVPlayer() {

}

int AVPlayer::Open(double time) {
//    if (readerThread == nullptr) {
//        readerThread = new AVReaderThread(sourcePath);
//        readerThread->Start();
//        return 0;
//    }

    if (syncThread == nullptr) {
        syncThread = new AVSyncThread(sourcePath, time);
        syncThread->Start();
        return 0;
    }
    return -1;
}

int AVPlayer::Stop() {
//    if (readerThread != nullptr) {
//        readerThread->Stop();
//        delete readerThread;
//        readerThread = nullptr;
//        return 0;
//    }

    if (syncThread != nullptr) {
        syncThread->Stop();
        delete syncThread;
        syncThread = nullptr;
        return 0;
    }
    return -1;
}

int AVPlayer::Play() {
    if (syncThread != nullptr) {
        syncThread->Play();
    }
    return 0;
}

int AVPlayer::Pause() {
    if (syncThread != nullptr) {
        syncThread->Pause();
    }
    return 0;
}

int AVPlayer::Seek(double time) {
    Stop();
    Open(time);
    return 0;
}

int AVPlayer::Compile(const char* compilePath) {
    return 0;
}
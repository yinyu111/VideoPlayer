//
// Created by 尹玉 on 2024/4/21.
//

#include "AVPlayer.h"

AVPlayer::AVPlayer(std::string _sourcePath) {
    sourcePath = _sourcePath;
}
AVPlayer::~AVPlayer() {

}

int AVPlayer::Open() {
//    if (readerThread == nullptr) {
//        readerThread = new AVReaderThread(sourcePath);
//        readerThread->Start();
//        return 0;
//    }

    if (syncThread == nullptr) {
        syncThread = new AVSyncThread(sourcePath);
        syncThread->Start();
        return 0;
    }
    return -1;
}

int AVPlayer::Play() {
    return 0;
}

int AVPlayer::Pause() {
    return 0;
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

int AVPlayer::Compile(const char* compilePath) {
    return 0;
}
int AVPlayer::Seek() {
    return 0;
}
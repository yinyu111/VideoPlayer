//
// Created by 尹玉 on 2024/4/21.
//

#ifndef VIDEOPLAYER_AVPLAYER_H
#define VIDEOPLAYER_AVPLAYER_H

#include <string>
#include <iostream>
#include "VideoThread/VideoThread.h"
#include "AVReader/AVReader.h"
#include "AVQueue/AVQueue.h"

class AVReaderThread : public VideoThread{
public:
    AVReaderThread(std::string _sourcePath);
    ~AVReaderThread();

    void run();

public:
    std::string sourcePath;
};

class AVPlayer {
public:
    AVPlayer(std::string _sourcePath);
    ~AVPlayer();

    int Open();

    int Play();
    int Pause();
    int Stop();

    int Compile(const char* compilePath);
    int Seek();

public:
    std::string sourcePath;
    AVReaderThread* readerThread = nullptr;
};


#endif //VIDEOPLAYER_AVPLAYER_H

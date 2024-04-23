//
// Created by 尹玉 on 2024/4/8.
//

#include "VideoThread.h"
#include <thread>

int VideoThread::Start()
{
    if (t == nullptr) {
        stopFlag = 0;
        t = new std::thread(&VideoThread::run, this);
    }

    return 0;
}

int VideoThread::Stop() {
    if (t != nullptr) {
        stopFlag = 1;
        t->join();
        delete t;
        t = nullptr;
    }
    return 0;
}
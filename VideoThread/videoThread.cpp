//
// Created by 尹玉 on 2024/4/8.
//

#include "videoThread.h"
#include <thread>

int videoThread::Start()
{
    std::thread t(&videoThread::run, this);
    t.detach();

    return 0;
}
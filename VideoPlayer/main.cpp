//
// Created by 尹玉 on 2024/4/21.
//

#include <thread>
#include <iostream>
#include "AVPlayer/AVPlayer.h"


 int main4() {
    AVPlayer* avPlayer = new AVPlayer("/Users/yinyu/code/testVideo/mumu.mp4");

    avPlayer->Open(0);
    avPlayer->Play();

//     std::this_thread::sleep_for(std::chrono::seconds(20));

    std::this_thread::sleep_for(std::chrono::seconds(5));

    avPlayer->Pause();

    std::cout << "=================Pause====================" << std::endl;

    std::this_thread::sleep_for(std::chrono::seconds(2));

    avPlayer->Play();

    std::this_thread::sleep_for(std::chrono::seconds(2));

    avPlayer->Stop();

    std::cout << "=================Stop====================" << std::endl;

    std::this_thread::sleep_for(std::chrono::seconds(2));

//    avPlayer->Seek(2);
//
//     std::cout << "=================Seek====================" << std::endl;
//
//     std::this_thread::sleep_for(std::chrono::seconds(20));

    return 0;
}
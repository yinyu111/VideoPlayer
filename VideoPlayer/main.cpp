//
// Created by 尹玉 on 2024/4/21.
//

#include <thread>
#include "AVPlayer/AVPlayer.h"


 int main() {
    AVPlayer* avPlayer = new AVPlayer("/Users/yinyu/code/testVideo/mumu.mp4");

    avPlayer->Open();
//    avPlayer->Play();

    std::this_thread::sleep_for(std::chrono::seconds(100));

    avPlayer->Stop();


    return 0;
}
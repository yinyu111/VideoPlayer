//
// Created by 尹玉 on 2024/4/21.
//

#include <unistd.h>
#include "AVPlayer/AVPlayer.h"


 int main() {
    AVPlayer* avPlayer = new AVPlayer("/Users/yinyu/code/testVideo/mumu.mp4");

    avPlayer->Open();
    avPlayer->Play();

    sleep(5000);

    avPlayer->Stop();


    return 0;
}
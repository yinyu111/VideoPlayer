//
// Created by 尹玉 on 2024/4/25.
//

#ifndef VIDEOPLAYER_AVTIME_H
#define VIDEOPLAYER_AVTIME_H

#include <chrono>

class AVTime {
public:
    AVTime();
    ~AVTime();

    static long long GetTime() {
        std::chrono::time_point<std::chrono::system_clock, std::chrono::milliseconds> tp = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now());
        auto tmp = std::chrono::duration_cast<std::chrono::milliseconds>(tp.time_since_epoch());
        return (long long)tmp.count();
    }
};

#endif //VIDEOPLAYER_AVTIME_H

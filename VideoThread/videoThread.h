//
// Created by 尹玉 on 2024/4/8.
//

#ifndef VIDEOPLAYER1_VIDEOTHREAD_H
#define VIDEOPLAYER1_VIDEOTHREAD_H

//模仿java线程 明确资源 清晰 正常回收资源/正常运行
// 达到线程安全
class VideoThread {
public:
    virtual void run() = 0;
    int Start();
    int Stop();

public:
    int stopFlag = 1;
    std::thread* t = nullptr;
};


#endif //VIDEOPLAYER1_VIDEOTHREAD_H

//
// Created by 尹玉 on 2024/4/20.
//

#ifndef VIDEOPLAYER_AVQUEUE_H
#define VIDEOPLAYER_AVQUEUE_H

#include <queue>
#include <mutex>

template<typename T>
class AVQueue {
public:
    AVQueue() {

    }
    ~AVQueue() {
        std::lock_guard<std::mutex> lck(mutex);
        while (queue.size() > 0) {
            queue.pop();
        }
    }

    int Push(T* t) {
        std::lock_guard<std::mutex> lck(mutex);
        queue.push(t);
        return 0;
    }

    int Pop(T** t) {
        std::lock_guard<std::mutex> lck(mutex);
        if (queue.size() > 0) {
            *t = queue.front();
            queue.pop();
            return 0;
        }
        return -1;
    }

    int GetSize() {
        std::lock_guard<std::mutex> lck(mutex);
        return queue.size();
    }

public:
    std::queue<T*> queue;
    std::mutex mutex;
};

#endif //VIDEOPLAYER_AVQUEUE_H

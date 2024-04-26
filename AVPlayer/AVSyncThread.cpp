//
// Created by 尹玉 on 2024/4/25.
//

#include "AVPlayer.h"
#include "AVUtils/AVTime.h"

AVSyncThread::AVSyncThread(std::string _sourcePath) {
    sourcePath = _sourcePath;
}

AVSyncThread::~AVSyncThread() {

}

void AVSyncThread::run() {
    AVReaderThread* readerThread = new AVReaderThread(sourcePath, this);
    readerThread->Start();

    long long startTime = AVTime::GetTime();

    AVReaderFrame* videoFrame = new AVReaderFrame();
    AVReaderFrame* audioFrame = new AVReaderFrame();

    while (!stopFlag) {
        long long currentTime = AVTime::GetTime();
        long long diffTime = currentTime - startTime;

        if (videoFrame == nullptr) {
            videoQueue.Pop(&videoFrame);
        }
        if (videoFrame != nullptr) {
            long long videoFramePTS = videoFrame->GetPTS();

            if (videoFramePTS < diffTime) {
                std::cout << "play videoFrame! PTSTime:" << videoFramePTS <<std::endl;
                delete videoFrame;
                videoFrame = nullptr;
            }
            else {
                // 否则
                // 这帧视频还不到播放的时候,程序进行自旋，或者去处理音频
            }

        }

        if (audioFrame == nullptr) {
            audioQueue.Pop(&audioFrame);
        }
        if (audioFrame != nullptr) {
            long long audioFramePTS = audioFrame->GetPTS();

            if (audioFramePTS < diffTime) {
                std::cout << "play audioFrame! PTSTime:" << audioFramePTS <<std::endl;
                delete audioFrame;
                audioFrame = nullptr;
            }
            else {
                // 否则
                // 这帧音频还不到播放的时候,程序进行自旋
            }

        }
    }

    readerThread->Stop();
}

int AVSyncThread::GetVideoQueueSize() {
    return videoQueue.GetSize();
}
int AVSyncThread::GetAudioQueueSize() {
    return audioQueue.GetSize();
}
int AVSyncThread::PushFrameToVideoQueue(AVReaderFrame* videoFrame) {
    return videoQueue.Push(videoFrame);
}
int AVSyncThread::PushFrameToAudioQueue(AVReaderFrame* audioFrame) {
    return audioQueue.Push(audioFrame);
}
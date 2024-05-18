//
// Created by 尹玉 on 2024/4/25.
//

#include <thread>
#include "AVPlayer.h"
#include "AVReader/AVManager.h"
#include "AVUtils/AVTime.h"

AVSyncThread::AVSyncThread(std::string _sourcePath, double _seekTime) {
    sourcePath = _sourcePath;
    seekTime = _seekTime;
    playerState = AVPlayerState::AV_STATE_INIT;
}

AVSyncThread::~AVSyncThread() {

}

void AVSyncThread::run() {
    AVReaderThread* readerThread = new AVReaderThread(sourcePath, this, seekTime);
    readerThread->Start();

//    RenderThread* renderThread = new RenderThread(2, 2);
//    renderThread->Start();

    long long startTime = AVTime::GetTime();
    long long puaseTime = 0;

    AVReaderFrame* videoFrame = new AVReaderFrame();
    AVReaderFrame* audioFrame = new AVReaderFrame();

    while (!stopFlag) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));

        long long pauseBeforeTime = AVTime::GetTime();
        while (playerState == AVPlayerState::AV_STATE_PAUSED) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
            //continue;
        }
        long long pauseAfterTime = AVTime::GetTime();
        puaseTime += (pauseAfterTime - pauseBeforeTime);

        long long currentTime = AVTime::GetTime();
        long long diffTime = currentTime - startTime;

        diffTime = diffTime - puaseTime;

        diffTime += (long long )seekTime * 1000;

        if (videoFrame == nullptr) {
            videoQueue.Pop(&videoFrame);
        }
        if (videoFrame != nullptr) {
            long long videoFramePTS = videoFrame->GetPTS();

            if (videoFramePTS < (long long)seekTime * 1000) {
                delete videoFrame;
                videoFrame = nullptr;
            }

            if (videoFramePTS < diffTime) {
                std::cout << "play videoFrame! PTSTime:" << videoFramePTS <<std::endl;

                if (videoFrame->GetWidth() != 0) {
                    AVRGBData* rgb = new AVRGBData(videoFrame->GetWidth(), videoFrame->GetHeigth());
                    videoFrame->GetRGBData(rgb->rgbData);
                    rgb->pts = videoFramePTS;

                    if (videoFrame->GetDurationSec() * 1000 <= videoFramePTS) {
                        rgb->isEOF = true;
                    }

                    renderQueue.Push(rgb);
                }

                //可能会内存泄漏 之后看下
//                delete videoFrame;
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

            if (audioFramePTS < (long long)seekTime * 1000) {
                delete audioFrame;
                audioFrame = nullptr;
            }

            if (audioFramePTS < diffTime) {
//                std::cout << "play audioFrame! PTSTime:" << audioFramePTS <<std::endl;
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

int AVSyncThread::Play() {
    playerState = AVPlayerState::AV_STATE_PLAYING;
    return 0;
}

int AVSyncThread::Pause() {
    playerState = AVPlayerState::AV_STATE_PAUSED;
    return 0;
}

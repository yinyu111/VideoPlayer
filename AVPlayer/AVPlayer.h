//
// Created by 尹玉 on 2024/4/21.
//

#ifndef VIDEOPLAYER_AVPLAYER_H
#define VIDEOPLAYER_AVPLAYER_H

#include <string>
#include <iostream>
#include "VideoThread/VideoThread.h"
#include "AVReader/AVReader.h"
#include "AVQueue/AVQueue.h"
#include "Render/Render.h"

enum DecoderType {
    DECODER_TYPE_UNKNOWN,
    DECODER_TYPE_VIDEO,
    DECODER_TYPE_AUDIO
};

enum AVPlayerState {
    AV_STATE_INIT,
    AV_STATE_PLAYING,
    AV_STATE_PAUSED,
    AV_STATE_STOPPED
};

class AVSyncThread : public VideoThread{
public:
    AVSyncThread(std::string _sourcePath, double time);
    ~AVSyncThread();

    virtual void run();

    int GetVideoQueueSize();
    int GetAudioQueueSize();
    int PushFrameToVideoQueue(AVReaderFrame* videoFrame);
    int PushFrameToAudioQueue(AVReaderFrame* audioFrame);

    int Play();
    int Pause();

public:
    AVQueue<AVReaderFrame> videoQueue;
    AVQueue<AVReaderFrame> audioQueue;

    AVQueue<AVRGBData> renderQueue;


    std::string sourcePath;
    AVPlayerState playerState;
    double seekTime;
    long long duration;

};

class AVReaderThread : public VideoThread{
public:
    AVReaderThread(std::string _sourcePath, AVSyncThread* _synvThread, double _seekTime);
    ~AVReaderThread();

    virtual void run();

public:
    std::string sourcePath;
    AVSyncThread* synvThread = nullptr;
    double seekTime;
};

class AVDecoderThread : public VideoThread {
public:
    AVDecoderThread(AVSyncThread* _synvThread);
    ~AVDecoderThread();

    int Init(AVReaderStream* readerStream, DecoderType _decoderType);
    int PutPacket(AVReaderPacket* readerPacket);
    int GetPacketQueueSize();

    virtual void run();

public:
    AVDecoder* decoder = nullptr;
    AVSyncThread* synvThread = nullptr;
    AVQueue<AVReaderPacket> packetQueue;

    DecoderType decoderType = DECODER_TYPE_UNKNOWN;
};

class AVPlayer {
public:
    AVPlayer(std::string _sourcePath);
    ~AVPlayer();

    int Open(double time);
    int Stop();

    int Play();
    int Pause();

    int Seek(double time);
    int Compile(const char* compilePath);

public:
    std::string sourcePath;
    AVReaderThread* readerThread = nullptr;

    AVSyncThread* syncThread = nullptr;
};


#endif //VIDEOPLAYER_AVPLAYER_H

//
// Created by 尹玉 on 2024/4/9.
//

#ifndef VIDEOPLAYER_AVREADER_H
#define VIDEOPLAYER_AVREADER_H

class AVPacketManager;
class AVFrameManager;
class AVFormatManager;
class AVDecoderManager;
class AVStreamManager;

class AVReaderPacket {
public:
    AVReaderPacket();
    ~AVReaderPacket();

    int GetIndex();
public:
    AVPacketManager* avPacketManager = nullptr;
};

class AVReaderFrame {
public:
    AVReaderFrame();
    ~AVReaderFrame();

    void VideoInfo();
    void AudioInfo();

    int GetWidth();
    int GetHeigth();
    long long GetPTS();

    int GetY(unsigned char* y);
    int GetU(unsigned char* u);
    int GetV(unsigned char* v);
public:
    AVFrameManager* avFrameManager = nullptr;
};

class AVReaderStream {
public:
    AVReaderStream();
    ~AVReaderStream();
public:
    int streamIndex = -1;
    int timebaseNum = 0;
    int timebaseDen = 0;
    AVStreamManager* avStreamManager = nullptr;
};

class AVReader {
public:
    AVReader();
    ~AVReader();

    int GetStreamCount();
    int GetStream(AVReaderStream* readerStream, int streamID);

    int GetVideoStreamIndex();
    int GetAudioStreamIndex();

    int Open(const char* sourcePath);
    int Close();
    int Read(AVReaderPacket* packet);
    int Seek(double seekTime);

private:
    AVFormatManager* avFormatManager = nullptr;

};

class AVDecoder {
public:
    AVDecoder();
    ~AVDecoder();

    int Init(AVReaderStream* stream);
    int SendPacket(AVReaderPacket* packet);
    int RecvFrame(AVReaderFrame** frame);
    int Close();
private:
    int timebaseNum = 0;
    int timebaseDen = 0;
    AVDecoderManager* avDecoderManager = nullptr;

};


#endif //VIDEOPLAYER_AVREADER_H

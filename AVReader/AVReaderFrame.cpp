//
// Created by 尹玉 on 2024/4/17.
//

#include "AVReader.h"
#include "AVManager.h"

AVReaderFrame::AVReaderFrame() {
    avFrameManager = new AVFrameManager();
    avFrameManager->avFrame = av_frame_alloc();
}

AVReaderFrame::~AVReaderFrame() {
    if (avFrameManager->avFrame != nullptr) {
        av_frame_free(&avFrameManager->avFrame);
        avFrameManager->avFrame = nullptr;
    }

    if (avFrameManager != nullptr) {
        delete avFrameManager;
        avFrameManager = nullptr;
    }
}

void AVReaderFrame::VideoInfo() {
    int width = avFrameManager->avFrame->width;
    int height = avFrameManager->avFrame->height;

    AVPixelFormat format = (AVPixelFormat)avFrameManager->avFrame->format;
    char* str = (char*)malloc(128);
    str = av_get_pix_fmt_string(str, 128, format);

    std::cout << "width: " << width << " height: " << height << std::endl;
    std::cout << "AVPixelFormat: " << str << std::endl;

    for (int i = 0; i < AV_NUM_DATA_POINTERS; ++i) {
        std::cout << "linesize: " << i << " value: " << avFrameManager->avFrame->linesize[i] << std::endl;
    }

    free(str);
    return;
}
void AVReaderFrame::AudioInfo() {

    //音频样本数（每个通道） 采样率
    int nb_samples = avFrameManager->avFrame->nb_samples;
    int sample_rate = avFrameManager->avFrame->sample_rate;

    AVSampleFormat format = (AVSampleFormat)avFrameManager->avFrame->format;
    char* str = (char*)malloc(128);
    str = av_get_sample_fmt_string(str, 128, format);

    std::cout << "nb_samples: " << nb_samples << std::endl;
    std::cout << "sample_rate: " << sample_rate << std::endl;
    std::cout << "AVSampleFormat: " << str << std::endl;

    for (int i = 0; i < AV_NUM_DATA_POINTERS; ++i) {
        std::cout << "linesize: " << i << " value: " << avFrameManager->avFrame->linesize[i] << std::endl;
    }

    free(str);
    return;
}

int AVReaderFrame::GetWidth() {
    return avFrameManager->avFrame->width;
}
int AVReaderFrame::GetHeigth() {
    return avFrameManager->avFrame->height;
}

int AVReaderFrame::GetY(unsigned char* y) {
    int width = GetWidth();
    int heigth = GetHeigth();

    for (int i = 0; i < heigth; ++i) {
        memcpy(y + width * i, avFrameManager->avFrame->data[0] + avFrameManager->avFrame->linesize[0] * i, width);
    }
     return 0;
}
int AVReaderFrame::GetU(unsigned char* u) {
    int width = GetWidth() / 2;
    int heigth = GetHeigth() / 2;

    for (int i = 0; i < heigth; ++i) {
        memcpy(u + width * i, avFrameManager->avFrame->data[1] + avFrameManager->avFrame->linesize[1] * i, width);
    }
    return 0;
}
int AVReaderFrame::GetV(unsigned char* v) {
    int width = GetWidth() / 2;
    int heigth = GetHeigth() / 2;

    for (int i = 0; i < heigth; ++i) {
        memcpy(v + width * i, avFrameManager->avFrame->data[2] + avFrameManager->avFrame->linesize[2] * i, width);
    }
    return 0;
}
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
long long AVReaderFrame::GetPTS() {
    return avFrameManager->ptsSec * 1000;
}

int AVReaderFrame::GetLineSize0() {
    return avFrameManager->avFrame->linesize[0];
}

int AVReaderFrame::GetData0(unsigned char* data0) {
    // 确保 avFrame 是有效的
    if (avFrameManager->avFrame == nullptr) {
        return -1; // 或者抛出异常或返回其他错误代码
    }

    // 获取 data[0] 数据
    memcpy(data0, avFrameManager->avFrame->data[0], avFrameManager->avFrame->linesize[0]);

    // 返回成功
    return 0;
}

extern "C" {
    #include <libavutil/imgutils.h>
    #include <libswscale/swscale.h>
}

int AVReaderFrame::GetRGBData(unsigned char* rgbData) {
    if (!avFrameManager->avFrame || !rgbData) {
        return -1; // 输入参数无效
    }

    int width = avFrameManager->avFrame->width;
    int height = avFrameManager->avFrame->height;

    //创建一个 SwsContext 用于缩放和格式转换
    struct SwsContext* swsContext = sws_getContext(
            width, height, (AVPixelFormat)avFrameManager->avFrame->format, // 输入图像的尺寸和格式
            width, height, AV_PIX_FMT_RGB24, // 输出图像的尺寸和格式
            SWS_BILINEAR, NULL, NULL, NULL // 缩放算法和过滤器参数
    );

    if (!swsContext) {
        return -2; // 无法创建 SwsContext
    }

    // 准备输出参数
    uint8_t* destData[4] = { rgbData }; // 输出数据数组，只包含一个平面
    int destLinesize[4] = { 3 * width }; // 每行输出数据的字节数，RGB24 格式每个像素 3 字节

    // 执行转换
    int result = sws_scale(
            swsContext, // SwsContext
            avFrameManager->avFrame->data, // 输入数据
            avFrameManager->avFrame->linesize, // 输入行大小
            0, height, // 输入图像的起始行和高度
            destData, // 输出数据
            destLinesize // 输出行大小
    );

    // 释放 SwsContext
    sws_freeContext(swsContext);

    if (result < 0) {
        return -3; // 转换失败
    }
    return 0; // 转换成功
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
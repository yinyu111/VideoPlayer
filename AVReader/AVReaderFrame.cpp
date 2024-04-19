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
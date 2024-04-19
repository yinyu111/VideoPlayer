//
// Created by 尹玉 on 2024/4/17.
//

#include "AVReader.h"
#include "AVManager.h"

AVReaderStream::AVReaderStream() {
    avStreamManager = new AVStreamManager();
    avStreamManager->codecPar = avcodec_parameters_alloc();
}

AVReaderStream::~AVReaderStream() {
    if (avStreamManager->codecPar != nullptr) {
        avcodec_parameters_free(&avStreamManager->codecPar);
        avStreamManager->codecPar = nullptr;
    }

    if (avStreamManager != nullptr) {
        delete avStreamManager;
        avStreamManager = nullptr;
    }
}
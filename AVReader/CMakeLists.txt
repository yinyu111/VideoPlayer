cmake_minimum_required(VERSION 3.27)

include_directories(../3rdpard/ffmpeg/include)

add_library(
        AVReader

        AVHeader.h
        AVReader.h
        AVManager.h
        AVReader.cpp
        AVReaderPacket.cpp
        AVReaderFrame.cpp

        AVDecoder.cpp
        AVReaderStream.cpp
)
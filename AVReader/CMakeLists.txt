cmake_minimum_required(VERSION 3.27)

include_directories(../)
include_directories(../3rdpard/ffmpeg/include)
link_directories(../3rdpard/ffmpeg/lib)

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

target_link_libraries(AVReader avcodec)
target_link_libraries(AVReader avdevice)
target_link_libraries(AVReader avformat)
target_link_libraries(AVReader avutil)
target_link_libraries(AVReader swresample)
target_link_libraries(AVReader swscale)
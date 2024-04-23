cmake_minimum_required(VERSION 3.27)

include_directories(../)
#include_directories(../3rdpard/ffmpeg/include)
link_directories(../3rdpard/ffmpeg/lib)

add_library (
        AVPlayer

        AVPlayer.h
        AVPlayer.cpp
        AVReaderThread.cpp
        AVDecoderThread.cpp
)

#add_executable (VideoPlayer "videoPlayer.cpp" "videoPlayer.h" "main.cpp")

target_link_libraries(AVPlayer VideoThread)
target_link_libraries(AVPlayer AVReader)

target_link_libraries(AVPlayer avcodec)
target_link_libraries(AVPlayer avdevice)
target_link_libraries(AVPlayer avformat)
target_link_libraries(AVPlayer avutil)
target_link_libraries(AVPlayer swresample)
target_link_libraries(AVPlayer swscale)
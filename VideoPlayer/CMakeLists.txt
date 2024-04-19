cmake_minimum_required(VERSION 3.27)

include_directories(../)
#include_directories(../3rdpard/ffmpeg/include)
link_directories(../3rdpard/ffmpeg/lib)

add_executable (VideoPlayer "videoPlayer.cpp" "videoPlayer.h")

target_link_libraries(VideoPlayer VideoThread)
target_link_libraries(VideoPlayer AVReader)

target_link_libraries(VideoPlayer avcodec)
target_link_libraries(VideoPlayer avdevice)
target_link_libraries(VideoPlayer avformat)
target_link_libraries(VideoPlayer avutil)
target_link_libraries(VideoPlayer swresample)
target_link_libraries(VideoPlayer swscale)
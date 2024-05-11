cmake_minimum_required(VERSION 3.27)

include_directories(../)
#include_directories(../3rdpard/ffmpeg/include)
link_directories(../3rdpard/ffmpeg/lib)

include_directories(../3rdpard/glfw/include)
include_directories(../3rdpard/glad/include)
link_directories(../3rdpard/glfw/lib)

add_executable (VideoPlayer "videoPlayer.cpp" "videoPlayer.h" "main.cpp")

target_link_libraries(VideoPlayer VideoThread)
target_link_libraries(VideoPlayer AVReader)
target_link_libraries(VideoPlayer AVPlayer)
target_link_libraries(VideoPlayer Render)

target_link_libraries(VideoPlayer avcodec)
target_link_libraries(VideoPlayer avdevice)
target_link_libraries(VideoPlayer avformat)
target_link_libraries(VideoPlayer avutil)
target_link_libraries(VideoPlayer swresample)
target_link_libraries(VideoPlayer swscale)

file(REAL_PATH ../3rdpard/glfw/lib/libglfw.3.4.dylib ABSOLUTE_PATH)
target_link_libraries(VideoPlayer ${ABSOLUTE_PATH})
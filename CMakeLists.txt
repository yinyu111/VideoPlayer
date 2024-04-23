cmake_minimum_required(VERSION 3.27)
project(VideoPlayer)

set(CMAKE_CXX_STANDARD 20)

#add_executable(VideoPlayer main.cpp)

add_subdirectory(VideoPlayer)
add_subdirectory(VideoThread)
add_subdirectory(AVReader)
add_subdirectory(AVPlayer)
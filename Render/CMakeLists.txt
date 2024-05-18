cmake_minimum_required(VERSION 3.27)

include_directories(../)

include_directories(../3rdpard/glfw/include)
include_directories(../3rdpard/glad/include)
link_directories(../3rdpard/glfw/lib)

add_library(
        Render
        ../3rdpard/glad/src/glad.c

        test.cpp
        Render.h
        RenderProgram.cpp
        RenderShader.cpp
        RenderVAO.cpp
        RenderThread.cpp
)

#target_link_libraries(Render VideoThread)
#target_link_libraries(Render AVReader)

file(REAL_PATH ../3rdpard/glfw/lib/libglfw.3.4.dylib ABSOLUTE_PATH)
target_link_libraries(Render ${ABSOLUTE_PATH})
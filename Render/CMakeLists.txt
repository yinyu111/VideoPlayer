cmake_minimum_required(VERSION 3.27)

# include_directories(../3rdpard/glfw/include/)
# link_directories(../3rdpard/glfw/lib/)

# include_directories(../3rdpard/glad/include/)

include_directories(../3rdpard/glfw/include)
include_directories(../3rdpard/glad/include)
link_directories(../3rdpard/glfw/lib)

add_library(
        Render
        ../3rdpard/glad/src/glad.c

        test.cpp
        test.h
)

file(REAL_PATH ../3rdpard/glfw/lib/libglfw.3.4.dylib ABSOLUTE_PATH)
target_link_libraries(Render ${ABSOLUTE_PATH})

#target_link_libraries(Render glfw.3.4)
cmake_minimum_required(VERSION 3.7)
project(src)

set(CMAKE_CXX_STANDARD 11)
set(SOURCE_FILES main.c gif_util.cpp gif_util.h)

add_library(
        giflib
        giflib/egif_lib.c
        giflib/dgif_lib.c
        giflib/gif_lib.h
        giflib/gif_err.c
        giflib/gif_font.c
        giflib/gif_hash.c
        giflib/gif_hash.h
        giflib/gif_lib_private.h
        giflib/gifalloc.c
        giflib/openbsd-reallocarray.c
        giflib/quantize.c
        giflib/gif_lib.h
)

add_executable(src ${SOURCE_FILES})

target_link_libraries(src giflib)
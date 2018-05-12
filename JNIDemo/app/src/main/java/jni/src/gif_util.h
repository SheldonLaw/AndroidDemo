//
// Created by sheldonluo on 2018/5/11.
//

#ifndef SRC_GIF_UTIL_H
#define SRC_GIF_UTIL_H

#ifdef __cplusplus
#define EXTERN extern "C"
#else
#define EXTERN
#endif

#include <stdlib.h>
#include <string.h>
#include "giflib/gif_lib.h"

typedef struct {
    int total_frame;
    int cur_frame;
} GifInfo;

EXTERN void loadGif(const char *path);
EXTERN SavedImage getNextFrame();
EXTERN ColorMapObject* getGlobalColorMap();


#endif //SRC_GIF_UTIL_H

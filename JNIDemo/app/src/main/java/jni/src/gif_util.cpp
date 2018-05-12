//
// Created by sheldonluo on 2018/5/11.
//
#include "gif_util.h"

GifFileType *gifFile;

void loadGif(const char *path) {



    int err;
    GifFileType *gifFileType = DGifOpenFileName(path, &err);
    DGifSlurp(gifFileType);

    // info
    GifInfo *gifInfo = (GifInfo *) malloc(sizeof(GifInfo));
    memset(gifInfo, 0, sizeof(GifInfo));
    gifInfo->total_frame = gifFileType->ImageCount;
//    gifInfo->cur_frame = 2;
    // add custom info
    gifFileType->UserData = gifInfo;

    gifFile = gifFileType;
}

SavedImage getNextFrame() {
    GifInfo *gifInfo = (GifInfo *) gifFile->UserData;

    // load cur frame
    SavedImage savedImg  = gifFile->SavedImages[gifInfo->cur_frame];


    // auto increase
    gifInfo->cur_frame += 1;
    if (gifInfo->cur_frame > gifInfo->total_frame -1) {
        gifInfo->cur_frame = 0;
    }

    return savedImg;
}

ColorMapObject* getGlobalColorMap() {
    return gifFile->Image.ColorMap;
}
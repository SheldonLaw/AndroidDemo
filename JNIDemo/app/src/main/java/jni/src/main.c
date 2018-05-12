#include "gif_util.h"


    int main() {

        char imgPath[] = "/Users/sheldonluo/workspace/AndroidDemo/JNIDemo/app/src/main/res/drawable/img.gif";

        // load gifImg with Giflib
        loadGif(imgPath);

        // load next frame()
        SavedImage savedImage = getNextFrame();
        GifImageDesc gifImageDesc = savedImage.ImageDesc;
        int *line;
        int pointpixels;
        ColorMapObject *colorMapObject = savedImage.ImageDesc.ColorMap;

        // 控制信息
        ExtensionBlock *controlBlock;
        for (int i = 0; i < savedImage.ExtensionBlockCount; ++i) {
            ExtensionBlock block = savedImage.ExtensionBlocks[i];
            if (savedImage.ExtensionBlocks[i].Function == GRAPHICS_EXT_FUNC_CODE) {
                controlBlock = &(savedImage.ExtensionBlocks[i]);
            }
        }
        if (controlBlock) {
            int a = controlBlock->Bytes[0] >> 2;
            int b = controlBlock->Bytes[0] & 3;
            int c = controlBlock->Bytes[1] >> 2;
            int d = controlBlock->Bytes[1] & 3;
        }

        for (int y=0;y<gifImageDesc.Height;++y) { //遍历行
//            line=px;

            //遍历列
            for (int x=0;x<gifImageDesc.Width;++x){
                //具体一个像素的索引
                pointpixels=y*gifImageDesc.Width + x;
                GifByteType gifByteType = savedImage.RasterBits[pointpixels]; //得到的是压缩数据
                //解压缩

                GifColorType gifColorType  = colorMapObject->Colors[gifByteType];
                //压缩的argb解压成RGB
                int r = gifColorType.Red;
                int g = gifColorType.Green;
                int b = gifColorType.Blue;

                int a = 0;
                //line[x]= Argb(255,gifColorType.Red ,gifColorType.Green,gifColorType.Blue);
            }
//            px=(int *) (char*)px+info.stride;//换行

        }

        return 0;
    }
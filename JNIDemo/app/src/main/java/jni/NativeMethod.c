//
// Created by sheldonluo on 2018/5/8.
// native implement
//

#include <string.h>
#include <jni.h>
#include "src/gif_util.h"
#include <android/bitmap.h>

/* This is a trivial JNI example where we use a native method
 * to return a new VM String. See the corresponding Java source
 * file located at:
 *
 *   E:\Lilac-Applications\Test\app\src\main\java\com\lilacouyang\firstjni\JniMethod.java
 */
jstring
Java_com_example_sheldonluo_jnidemo_NativeMethod_print( JNIEnv* env, jclass type, jstring msg )
{
#if defined(__arm__)
  #if defined(__ARM_ARCH_7A__)
    #if defined(__ARM_NEON__)
      #if defined(__ARM_PCS_VFP)
        #define ABI "armeabi-v7a/NEON (hard-float)"
      #else
        #define ABI "armeabi-v7a/NEON"
      #endif
    #else
      #if defined(__ARM_PCS_VFP)
        #define ABI "armeabi-v7a (hard-float)"
      #else
        #define ABI "armeabi-v7a"
      #endif
    #endif
  #else
   #define ABI "armeabi"
  #endif
#elif defined(__i386__)
   #define ABI "x86"
#elif defined(__x86_64__)
   #define ABI "x86_64"
#elif defined(__mips64)  /* mips64el-* toolchain defines __mips__ too */
   #define ABI "mips64"
#elif defined(__mips__)
   #define ABI "mips"
#elif defined(__aarch64__)
   #define ABI "arm64-v8a"
#else
   #define ABI "unknown"
#endif

    return msg;
}

void Java_com_example_sheldonluo_jnidemo_NativeMethod_loadGif
  (JNIEnv* env, jclass type, jstring path) {
  const char *cPath = (*env)->GetStringUTFChars(env, path, 0);
  loadGif(cPath);
  (*env)->ReleaseStringUTFChars(env, path, cPath);
}

// TODO: 为了提升性能，考虑对第一帧进行缓存
void Java_com_example_sheldonluo_jnidemo_NativeMethod_getNextFrame
    (JNIEnv* env, jclass type, jobject jbitmap) {

    SavedImage savedImage = getNextFrame();

/*
    jclass cls = (*env)->GetObjectClass(env, jbitmap);
    jmethodID mid = (*env)->GetMethodID(env, cls, "setHeight", "(I)V");
    (*env)->CallVoidMethod(env, jbitmap, mid, savedImage.ExtensionBlockCount);
*/

    // write img into jbitmap
    AndroidBitmapInfo info;
    void *pixels;
    AndroidBitmap_getInfo(env, jbitmap, &info);
    AndroidBitmap_lockPixels(env, jbitmap, &pixels);
    int *px = (int *) pixels; //整幅图片的首地址
    int *line;//每一行的首地址
    int pointpixels;//在saveimage里面的索引rasterbits
//    TODO: 颜色表要兼容全局颜色表的情况
    ColorMapObject *colorMapObject = savedImage.ImageDesc.ColorMap;  //根据颜色列表压缩
//    ColorMapObject *colorMapObject = getGlobalColorMap();  //根据颜色列表压缩

    // 控制信息
    ExtensionBlock *controlBlock;
    for (int i = 0; i < savedImage.ExtensionBlockCount; ++i) {
        ExtensionBlock block = savedImage.ExtensionBlocks[i];
        if (savedImage.ExtensionBlocks[i].Function == GRAPHICS_EXT_FUNC_CODE) {
            controlBlock = &(savedImage.ExtensionBlocks[i]);
        }
    }
    if (controlBlock) {
        // 解析控制信息
        int DisposalMode = controlBlock->Bytes[0] >> 2;
        int UserInputFlag = controlBlock->Bytes[0] & 3;
        int DelayTime = controlBlock->Bytes[1] >> 2; // 单位为0.01s
        int TransparentColor = controlBlock->Bytes[1] & 3;
    }


    GifImageDesc frameinfo= savedImage.ImageDesc;

    for (int y=frameinfo.Top;y<frameinfo.Top+frameinfo.Height;++y) { //遍历行
        line=px;

        for (int x=frameinfo.Left;x<frameinfo.Left+frameinfo.Width;++x){


            pointpixels=(y-frameinfo.Top)*frameinfo.Width+x-frameinfo.Left;
            GifByteType gifByteType = savedImage.RasterBits[pointpixels];

            // 如果返回空，说明该位置不需要重绘，具体请参考上面解析得到的DisposalMode
            if (gifByteType == NULL) continue;

            //decode color
            GifColorType gifColorType  = colorMapObject->Colors[gifByteType];
            int r = gifColorType.Red;
            int g = gifColorType.Green;
            int b = gifColorType.Blue;


            //303F9F
//            int blue = (int) ((line[x] & 0xFF0000) >> 16);
//            int green = (int)((line[x] & 0x00FF00) >> 8);
//            int red = (int) (line[x] & 0x0000FF);

            // encode ABGR
            line[x] =
                    ((255<<24) & 0xFF000000) |
                    ((b<< 16) & 0x00FF0000) |
                    ((g << 8) & 0x0000FF00) |
                    (r & 0x000000FF);

            // BGR
//            line[x] = 0xFFA64D82;
            int ddd = 0;
        }
        px=(int *) (char*)px+info.stride / 4; //jump to new line， why 4: 存储的是颜色表的索引，并不是rgba

    }
    AndroidBitmap_unlockPixels(env, jbitmap);

}
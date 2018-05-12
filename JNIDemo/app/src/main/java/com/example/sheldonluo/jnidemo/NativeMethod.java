package com.example.sheldonluo.jnidemo;

import android.graphics.Bitmap;

public class NativeMethod {

    static {
        /**
         *  load native lib
         */
        System.loadLibrary("NativeMethod");
    }

    /**
     * native methods
     */

    public static native String print(String msg);

    public static native void loadGif(String path);

    public static native void getNextFrame(Bitmap bitmap);
}


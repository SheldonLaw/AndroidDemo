package com.example.sheldonluo.jnidemo;

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

}


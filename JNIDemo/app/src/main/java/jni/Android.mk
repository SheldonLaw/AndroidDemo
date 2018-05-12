
LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := NativeMethod
LOCAL_SRC_FILES := NativeMethod.c \
src/gif_util.cpp \
src/giflib/dgif_lib.c \
src/giflib/gif_err.c \
src/giflib/gif_font.c \
src/giflib/gif_hash.c \
src/giflib/gifalloc.c \
src/giflib/openbsd-reallocarray.c \
src/giflib/quantize.c

LOCAL_LDLIBS    := -ljnigraphics

include $(BUILD_SHARED_LIBRARY)
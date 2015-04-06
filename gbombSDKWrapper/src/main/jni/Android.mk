LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := gbombsdk_share
LOCAL_SRC_FILES := $(TARGET_ARCH_ABI)/libgbombsdk.so
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/include
LOCAL_LDLIBS := -lz
include $(PREBUILT_SHARED_LIBRARY)

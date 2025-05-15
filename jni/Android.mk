LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE    := dft
LOCAL_SRC_FILES := ../dft.c
LOCAL_EXPORT_C_INCLUDES := .
include $(BUILD_SHARED_LIBRARY)
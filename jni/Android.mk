# Android.mk
LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := libgodot
LOCAL_SRC_FILES := $(PWD)/godot-cpp/bin/$(SC_ARCH)/libgodot.$(SC_TARGET).a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
ifeq ($(SC_CLANG), true)
	NDK_TOOLCHAIN_VERSION := clang
else
	NDK_TOOLCHAIN_VERSION := gcc
endif
LOCAL_MODULE := lib$(notdir $(PWD))
LOCAL_CPPFLAGS := -std=c++17
LOCAL_CPP_FEATURES := rtti exceptions
LOCAL_LDLIBS := -llog

LOCAL_MODULE := $(LOCAL_MODULE)

ifeq ($(SC_TARGET),debug)
	LOCAL_CPPFLAGS := $(LOCAL_CPPFLAGS) -fPIC -g -Og -DDEBUG
else
	LOCAL_CPPFLAGS := $(LOCAL_CPPFLAGS) -fPIC -O3
endif

LOCAL_SRC_FILES := $(shell find $$PWD"/source" -name "*.cpp" )

LOCAL_C_INCLUDES := \
$(PWD)/godot-cpp/godot_headers \
$(PWD)/godot-cpp/include \
$(PWD)/godot-cpp/include/gen \
$(PWD)/godot-cpp/include/core

LOCAL_SHARED_LIBRARIES := libgodot

include $(BUILD_SHARED_LIBRARY)
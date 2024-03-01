LOCAL_PATH := $(call my-dir)
MAIN_LOCAL_PATH := $(call my-dir)

# ============================================================================#
include $(CLEAR_VARS)
LOCAL_MODULE            := libcurl
LOCAL_SRC_FILES         := FangCyR/Validation/curl_openssl/curl-android-$(TARGET_ARCH_ABI)/lib/libcurl.a

include $(PREBUILT_STATIC_LIBRARY)
# ============================================================================#

include $(CLEAR_VARS)
LOCAL_MODULE            := libssl
LOCAL_SRC_FILES         := FangCyR/Validation/curl_openssl/openssl-android-$(TARGET_ARCH_ABI)/lib/libssl.a

include $(PREBUILT_STATIC_LIBRARY)
# ============================================================================#

include $(CLEAR_VARS)
LOCAL_MODULE            := libcrypto
LOCAL_SRC_FILES         := FangCyR/Validation/curl_openssl/openssl-android-$(TARGET_ARCH_ABI)/lib/libcrypto.a

include $(PREBUILT_STATIC_LIBRARY)
# ============================================================================#

include $(CLEAR_VARS)
LOCAL_MODULE            := libharmes
LOCAL_SRC_FILES         := FangCyR/Engine/Dobby/$(TARGET_ARCH_ABI)/libharmes.a

include $(PREBUILT_STATIC_LIBRARY)
# ============================================================================#

## Keystone static lib link
include $(CLEAR_VARS)
LOCAL_MODULE    := Keystone
LOCAL_SRC_FILES := FangCyR/Engine/Deps/Keystone/libs-android/$(TARGET_ARCH_ABI)/libkeystone.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)

LOCAL_MODULE           := AkSoundEngine2

LOCAL_CFLAGS           := -Wno-error=format-security -fvisibility=hidden -ffunction-sections -fdata-sections -w
LOCAL_CFLAGS           += -fno-rtti -fno-exceptions -fpermissive
LOCAL_CPPFLAGS         := -Wno-error=format-security -fvisibility=hidden -ffunction-sections -fdata-sections -w -fexceptions -Werror -s -std=c++17
LOCAL_CPPFLAGS         += -Wno-error=c++11-narrowing -fms-extensions -fno-rtti -fno-exceptions -fpermissive
LOCAL_LDFLAGS          += -Wl,--gc-sections,--strip-all, -llog
LOCAL_LDLIBS           := -llog -landroid -lEGL -lGLESv3 -lGLESv2 -lGLESv1_CM -lz -ldl
LOCAL_ARM_MODE         := arm

LOCAL_C_INCLUDES       += $(LOCAL_PATH)
LOCAL_C_INCLUDES       := $(LOCAL_PATH)/FangCyR/Validation/curl_openssl/curl-android-$(TARGET_ARCH_ABI)/include
LOCAL_C_INCLUDES       += $(LOCAL_PATH)/FangCyR/Validation/curl_openssl/openssl-android-$(TARGET_ARCH_ABI)/include
LOCAL_C_INCLUDES       += $(LOCAL_PATH)/FangCyR/Engine/Deps/Keystone/include
LOCAL_C_INCLUDES       += $(LOCAL_PATH)/FangCyR/Engine/Elf/include

LOCAL_STATIC_LIBRARIES := libharmes libcurl libssl libcrypto Keystone
LOCAL_CPP_FEATURES     := exceptions

FILE_LIST              := $(wildcard $(LOCAL_PATH)/ImGui/*.c*)
FILE_LIST              += $(wildcard $(LOCAL_PATH)/FangCyR/Engine/Elf/*.c*)
FILE_LIST              += $(wildcard $(LOCAL_PATH)/FangCyR/Engine/KittyMemory/*.c*)
FILE_LIST              += $(wildcard $(LOCAL_PATH)/*.c*)

LOCAL_SRC_FILES        := $(FILE_LIST:$(LOCAL_PATH)/%=%)

include $(BUILD_SHARED_LIBRARY)
# ============================================================================

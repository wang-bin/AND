/*
 * AND: Android Native Dev in Modern C++ based on JMI
 * Copyright (C) 2026 Wang Bin - wbsecg1@gmail.com
 * https://github.com/wang-bin/AND
 * https://github.com/wang-bin/JMI
 * MIT License
 */

#pragma once

#include "surface_texture_jni.hpp"
#include "android.graphics.SurfaceTexture.hpp"
#include <android/surface_texture_jni.h>

namespace ndk {
namespace android {

struct ASurfaceTexture {
    ::ASurfaceTexture* ndk_{};
    jmi::android::graphics::SurfaceTexture jni_{};
};

ASurfaceTexture* fromJmi(jmi::android::graphics::SurfaceTexture&& obj);
ASurfaceTexture* fromNdk(::ASurfaceTexture* obj);
::ASurfaceTexture* toNdk(const ASurfaceTexture* obj);

} // namespace android
} // namespace ndk
/*
 * AND: Android Native Dev in Modern C++ based on JMI
 * Copyright (C) 2026 Wang Bin - wbsecg1@gmail.com
 * https://github.com/wang-bin/AND
 * https://github.com/wang-bin/JMI
 * MIT License
 */

#pragma once

#include "surface_texture.hpp"
#include <jni.h>

namespace ndk {
namespace android {

bool isASurfaceTextureNdk();
void setASurfaceTextureNdk(bool value);

ASurfaceTexture* ASurfaceTexture_fromSurfaceTexture(JNIEnv* env, jobject surfacetexture);

} // namespace android
} // namespace ndk

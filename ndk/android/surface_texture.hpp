/*
 * AND: Android Native Dev in Modern C++ based on JMI
 * Copyright (C) 2026 Wang Bin - wbsecg1@gmail.com
 * https://github.com/wang-bin/AND
 * https://github.com/wang-bin/JMI
 * MIT License
 */

#pragma once

#include <stdint.h>

struct ANativeWindow;

namespace ndk {
namespace android {

struct ASurfaceTexture;

void ASurfaceTexture_release(ASurfaceTexture* st);

ANativeWindow* ASurfaceTexture_acquireANativeWindow(ASurfaceTexture* st);

int ASurfaceTexture_attachToGLContext(ASurfaceTexture* st, uint32_t texName);

int ASurfaceTexture_detachFromGLContext(ASurfaceTexture* st);

int ASurfaceTexture_updateTexImage(ASurfaceTexture* st);

void ASurfaceTexture_getTransformMatrix(ASurfaceTexture* st, float mtx[16]);

int64_t ASurfaceTexture_getTimestamp(ASurfaceTexture* st);

} // namespace android
} // namespace ndk

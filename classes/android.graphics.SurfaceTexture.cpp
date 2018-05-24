/*
 * AND: Android Native Dev in Modern C++ based on JMI
 * Copyright (C) 2018 Wang Bin - wbsecg1@gmail.com
 * https://github.com/wang-bin/AND
 * https://github.com/wang-bin/JMI
 * MIT License
 */

#include "android.graphics.SurfaceTexture.hpp"
#include "JMIUtils.hpp"
namespace jmi {
namespace android {
namespace graphics {
JMI_DEFINE(void, SurfaceTexture::attachToGLContext, JMI_ARG1(jint))
JMI_DEFINE(void, SurfaceTexture::detachFromGLContext, JMI_ARG0())
JMI_DEFINE_CONST(jlong, SurfaceTexture::getTimestamp, JMI_ARG0())
JMI_DEFINE_CONST(void, SurfaceTexture::getTransformMatrix, JMI_ARG1(std::reference_wrapper<jfloat[16]>))
JMI_DEFINE_CONST(jboolean, SurfaceTexture::isReleased, JMI_ARG0())
JMI_DEFINE(void, SurfaceTexture::release, JMI_ARG0())
JMI_DEFINE(void, SurfaceTexture::releaseTexImage, JMI_ARG0())
JMI_DEFINE(void, SurfaceTexture::setDefaultBufferSize, JMI_ARG2(jint, jint))
JMI_DEFINE(void, SurfaceTexture::setOnFrameAvailableListener, JMI_ARG1(std::reference_wrapper<const SurfaceTexture::OnFrameAvailableListener>))
JMI_DEFINE(void, SurfaceTexture::updateTexImage, JMI_ARG0())
} // namespace graphics
} // namespace android
} // namespace jmi
/*
 * AND: Android Native Dev in Modern C++ based on JMI
 * Copyright (C) 2018 Wang Bin - wbsecg1@gmail.com
 * https://github.com/wang-bin/AND
 * https://github.com/wang-bin/JMI
 * MIT License
 */

#include "android.media.AudioTrack.hpp"
#include "JMIUtils.hpp"
#include <iostream>
namespace jmi {
namespace android {
namespace media {
JMI_DEFINE_STATIC(jint, AudioTrack::getMinBufferSize, JMI_ARG3(jint, jint, jint))
JMI_DEFINE_STATIC(jfloat, AudioTrack::getMaxVolume, JMI_ARG0())
JMI_DEFINE(void, AudioTrack::play, JMI_ARG0())
JMI_DEFINE(void, AudioTrack::stop, JMI_ARG0())
JMI_DEFINE(void, AudioTrack::pause, JMI_ARG0())
JMI_DEFINE(void, AudioTrack::flush, JMI_ARG0())
JMI_DEFINE(void, AudioTrack::release, JMI_ARG0())
JMI_DEFINE_CONST(jint, AudioTrack::getState, JMI_ARG0())
JMI_DEFINE(jint, AudioTrack::write, JMI_ARG3(jbyteArray, jint, jint))
JMI_DEFINE(jint, AudioTrack::write, JMI_ARG3(jshortArray, jint, jint))
JMI_DEFINE(jint, AudioTrack::write, JMI_ARG4(jfloatArray, jint, jint, jint))
JMI_DEFINE(jint, AudioTrack::setVolume, JMI_ARG1(jfloat))
JMI_DEFINE(jint, AudioTrack::setStereoVolume, JMI_ARG2(jfloat, jfloat))
} // namespace media
} // namespace android
} // namespace jmi
/*
 * AND: Android Native Dev in Modern C++ based on JMI
 * Copyright (C) 2018-2019 Wang Bin - wbsecg1@gmail.com
 * https://github.com/wang-bin/AND
 * https://github.com/wang-bin/JMI
 * MIT License
 */

#include "android.media.MediaCodec.hpp"
#include "JMIUtils.hpp"
#include <iostream>
#include <vector>
namespace jmi {
namespace android {
namespace media {
jint MediaCodec::BufferInfo::offset(jint* value)
{
    constexpr const char* kName = __func__;
    struct F : public jmi::FieldTag { static const char* name() { return kName;}};
    auto f = field<F, jint>();
    if (value)
        f = jint(*value);
    return f;
}

jint MediaCodec::BufferInfo::size(jint* value)
{
    constexpr const char* kName = __func__;
    struct F : public jmi::FieldTag { static const char* name() { return kName;}};
    auto f = field<F, jint>();
    if (value)
        f = jint(*value);
    return f;
}

jlong MediaCodec::BufferInfo::presentationTimeUs(jlong* value)
{
    constexpr const char* kName = __func__;
    struct F : public jmi::FieldTag { static const char* name() { return kName;}};
    auto f = field<F, jlong>();
    if (value)
        f = jlong(*value);
    return f;
}

jint MediaCodec::BufferInfo::flags(jint* value)
{
    constexpr const char* kName = __func__;
    struct F : public jmi::FieldTag { static const char* name() { return kName;}};
    auto f = field<F, jint>();
    if (value)
        f = jint(*value);
    return f;
}

JMI_DEFINE_STATIC(MediaCodec, MediaCodec::createDecoderByType, JMI_ARG1(const char*))
JMI_DEFINE_STATIC(MediaCodec, MediaCodec::createEncoderByType, JMI_ARG1(const char*))
JMI_DEFINE_STATIC(MediaCodec, MediaCodec::createByCodecName, JMI_ARG1(const char*))
JMI_DEFINE_CONST(std::string, MediaCodec::getName, JMI_ARG0())
JMI_DEFINE(void, MediaCodec::release, JMI_ARG0())
JMI_DEFINE(void, MediaCodec::configure, JMI_ARG4(const MediaFormat&, const view::Surface&, const MediaCrypto&, jint))
JMI_DEFINE(void, MediaCodec::start, JMI_ARG0())
JMI_DEFINE(void, MediaCodec::stop, JMI_ARG0())
JMI_DEFINE(void, MediaCodec::flush, JMI_ARG0())
JMI_DEFINE(void, MediaCodec::signalEndOfInputStream, JMI_ARG0())
JMI_DEFINE_CONST(MediaFormat, MediaCodec::getInputFormat, JMI_ARG0())
JMI_DEFINE_CONST(MediaFormat, MediaCodec::getOutputFormat, JMI_ARG0())
JMI_DEFINE(void, MediaCodec::queueInputBuffer, JMI_ARG5(jint, jint, jint, jlong, jint))
JMI_DEFINE(jint, MediaCodec::dequeueInputBuffer, JMI_ARG1(jlong))
JMI_DEFINE(jint, MediaCodec::dequeueOutputBuffer, JMI_ARG2(BufferInfo&, jlong))
JMI_DEFINE(jint, MediaCodec::dequeueOutputBuffer, JMI_ARG2(std::reference_wrapper<BufferInfo>, jlong))
JMI_DEFINE(void, MediaCodec::releaseOutputBuffer, JMI_ARG2(jint, jboolean))
JMI_DEFINE(void, MediaCodec::releaseOutputBuffer, JMI_ARG2(jint, jlong))
JMI_DEFINE(void, MediaCodec::setVideoScalingMode, JMI_ARG1(jint))
JMI_DEFINE_CONST(MediaFormat, MediaCodec::getOutputFormat, JMI_ARG1(jint))
JMI_DEFINE_CONST(std::vector<java::nio::ByteBuffer>, MediaCodec::getInputBuffers, JMI_ARG0())
JMI_DEFINE_CONST(std::vector<java::nio::ByteBuffer>, MediaCodec::getOutputBuffers, JMI_ARG0())
JMI_DEFINE_CONST(java::nio::ByteBuffer, MediaCodec::getInputBuffer, JMI_ARG1(jint))
JMI_DEFINE_CONST(java::nio::ByteBuffer, MediaCodec::getOutputBuffer, JMI_ARG1(jint))
} // namespace media
} // namespace android
} // namespace jmi
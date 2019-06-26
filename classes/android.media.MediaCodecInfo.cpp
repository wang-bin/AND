/*
 * AND: Android Native Dev in Modern C++ based on JMI
 * Copyright (C) 2018-2019 Wang Bin - wbsecg1@gmail.com
 * https://github.com/wang-bin/AND
 * https://github.com/wang-bin/JMI
 * MIT License
 */
#include "android.media.MediaCodecInfo.hpp"
#include "JMIUtils.hpp"
namespace jmi {
namespace android {
namespace media {

jint MediaCodecInfo::CodecProfileLevel::level() const
{
    constexpr const char* kName = __func__;
    struct F : public jmi::FieldTag { static const char* name() { return kName;}};
    auto f = field<F, jint>();
    return f;
}

jint MediaCodecInfo::CodecProfileLevel::profile() const
{
    constexpr const char* kName = __func__;
    struct F : public jmi::FieldTag { static const char* name() { return kName;}};
    auto f = field<F, jint>();
    return f;
}

std::vector<jint> MediaCodecInfo::CodecCapabilities::colorFormats() const
{
    constexpr const char* kName = __func__;
    struct F : public jmi::FieldTag { static const char* name() { return kName;}};
    auto f = field<F, std::vector<jint>>();
    return f;
}

std::vector<MediaCodecInfo::CodecProfileLevel> MediaCodecInfo::CodecCapabilities::profileLevels() const
{
    constexpr const char* kName = __func__;
    struct F : public jmi::FieldTag { static const char* name() { return kName;}};
    auto f = field<F, std::vector<CodecProfileLevel>>();
    return f;
}

JMI_DEFINE_STATIC(MediaCodecInfo::CodecCapabilities, MediaCodecInfo::CodecCapabilities::createFromProfileLevel, JMI_ARG3(const char*, jint, jint))
JMI_DEFINE_CONST(MediaCodecInfo::AudioCapabilities,  MediaCodecInfo::CodecCapabilities::getAudioCapabilities, JMI_ARG0())
JMI_DEFINE_CONST(MediaCodecInfo::VideoCapabilities,  MediaCodecInfo::CodecCapabilities::getVideoCapabilities, JMI_ARG0())
JMI_DEFINE_CONST(MediaCodecInfo::EncoderCapabilities,  MediaCodecInfo::CodecCapabilities::getEncoderCapabilities, JMI_ARG0())
JMI_DEFINE_CONST(MediaFormat,  MediaCodecInfo::CodecCapabilities::getDefaultFormat, JMI_ARG0())
JMI_DEFINE_CONST(jint,  MediaCodecInfo::CodecCapabilities::getMaxSupportedInstances, JMI_ARG0())
JMI_DEFINE_CONST(std::string,  MediaCodecInfo::CodecCapabilities::getMimeType, JMI_ARG0())
JMI_DEFINE_CONST(jboolean,  MediaCodecInfo::CodecCapabilities::isFeatureRequired, JMI_ARG1(const char*))
JMI_DEFINE_CONST(jboolean,  MediaCodecInfo::CodecCapabilities::isFeatureSupported, JMI_ARG1(const char*))
JMI_DEFINE_CONST(jboolean,  MediaCodecInfo::CodecCapabilities::isFormatSupported, JMI_ARG1(MediaFormat))
JMI_DEFINE_CONST(MediaCodecInfo::CodecCapabilities, MediaCodecInfo::getCapabilitiesForType, JMI_ARG1(const char*))
JMI_DEFINE_CONST(std::string, MediaCodecInfo::getName, JMI_ARG0())
JMI_DEFINE_CONST(std::vector<std::string>, MediaCodecInfo::getSupportedTypes, JMI_ARG0())
JMI_DEFINE_CONST(jboolean, MediaCodecInfo::isEncoder, JMI_ARG0())

JMI_DEFINE_CONST(jboolean,  MediaCodecInfo::AudioCapabilities::isSampleRateSupported, JMI_ARG1(jint))
JMI_DEFINE_CONST(jint,  MediaCodecInfo::AudioCapabilities::getMaxInputChannelCount, JMI_ARG0())
JMI_DEFINE_CONST(std::vector<jint>,  MediaCodecInfo::AudioCapabilities::getSupportedSampleRates, JMI_ARG0())

JMI_DEFINE_CONST(jboolean,  MediaCodecInfo::VideoCapabilities::areSizeAndRateSupported, JMI_ARG3(jint, jint, jdouble))
JMI_DEFINE_CONST(jboolean,  MediaCodecInfo::VideoCapabilities::isSizeSupported, JMI_ARG2(jint, jint))
JMI_DEFINE_CONST(jint,  MediaCodecInfo::VideoCapabilities::getHeightAlignment, JMI_ARG0())
JMI_DEFINE_CONST(jint,  MediaCodecInfo::VideoCapabilities::getWidthAlignment, JMI_ARG0())

JMI_DEFINE_CONST(jboolean,  MediaCodecInfo::EncoderCapabilities::isBitrateModeSupported, JMI_ARG1(jint))
} // namespace media
} // namespace android
} // namespace jmi
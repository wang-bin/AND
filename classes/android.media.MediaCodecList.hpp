/*
 * AND: Android Native Dev in Modern C++ based on JMI
 * Copyright (C) 2018-2021 Wang Bin - wbsecg1@gmail.com
 * https://github.com/wang-bin/AND
 * https://github.com/wang-bin/JMI
 * MIT License
 */
#pragma once
#include "jmi/jmi.h"
#include "android.media.MediaCodecInfo.hpp"

namespace jmi {
namespace android {
namespace media {
class MediaCodecList : public jmi::JObject<MediaCodecList> { // inherits JObject so that it can be a return type like primitive types
public:
    enum {
        ALL_CODECS = 1, // api21
        REGULAR_CODECS = 0, //api21
    };

    using Base = jmi::JObject<MediaCodecList>;
    using Base::Base; // inherits ctors
    static constexpr auto name() { return JMISTR("android/media/MediaCodecList");} // required if derive from JObject<>
    // DO NOT forget to call create(int kind) for api21
    static jint getCodecCount(); // deprecated in api21. Use getCodecInfos() instead
    static MediaCodecInfo getCodecInfoAt(int index); // deprecated in api21. Use getCodecInfos() instead
    std::string findDecoderForFormat(MediaFormat format) const; // return string instead of char*
    std::string findEncoderForFormat(MediaFormat format) const;
    std::vector<MediaCodecInfo> getCodecInfos() const; // api21
};
} // namespace media
} // namespace android
} // namespace jmi
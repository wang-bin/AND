/*
 * AND: Android Native Dev in Modern C++ based on JMI
 * Copyright (C) 2018-2021 Wang Bin - wbsecg1@gmail.com
 * https://github.com/wang-bin/AND
 * https://github.com/wang-bin/JMI
 * MIT License
 */

#pragma once
#include "jmi/jmi.h"
#include "java.nio.ByteBuffer.hpp"

namespace jmi {
namespace android {
namespace media {
class MediaFormat : public jmi::JObject<MediaFormat> { // inherits JObject so that it can be a return type like primitive types
public:
    using Base = jmi::JObject<MediaFormat>;
    using Base::Base; // inherits ctors
    static constexpr auto name() { return JMISTR("android/media/MediaFormat");} // required if derive from JObject<>
    // DO NOT forget to call create()
    jboolean containsKey(const char* name) const;
    std::string toString() const;
    java::nio::ByteBuffer getByteBuffer(const char* name) const;
    jfloat getFloat(const char* name) const;
    jint getInteger(const char* name) const;
    jlong getLong(const char* name) const;
    std::string getString(const char* name) const;

    void setByteBuffer(const char* name, const java::nio::ByteBuffer& value);
    void setFloat(const char* name, float value);
    void setInteger(const char* name, jint value);
    void setLong(const char* name, jlong value);
    void setString(const char* name, const char* value);

// the following keys exists in api <= 19(default 16)
    constexpr static const char* KEY_AAC_PROFILE = "aac-profile";
    constexpr static const char* KEY_BIT_RATE = "bitrate";
    constexpr static const char* KEY_CHANNEL_COUNT = "channel-count";
    constexpr static const char* KEY_CHANNEL_MASK = "channel-mask";
    constexpr static const char* KEY_COLOR_FORMAT = "color-format";
    constexpr static const char* KEY_CSD = "csd"; // ?
    constexpr static const char* KEY_CSD_0 = "csd-0"; // ?
    constexpr static const char* KEY_CSD_1 = "csd-1"; // ?
    constexpr static const char* KEY_CSD_2 = "csd-2"; // ?
    constexpr static const char* KEY_DURATION = "durationUs";
    constexpr static const char* KEY_FLAC_COMPRESSION_LEVEL = "flac-compression-level";
    constexpr static const char* KEY_FRAME_RATE = "frame-rate";
    constexpr static const char* KEY_HEIGHT = "height";
    constexpr static const char* KEY_IS_ADTS = "is-adts";
    constexpr static const char* KEY_IS_AUTOSELECT = "is-autoselect";
    constexpr static const char* KEY_IS_DEFAULT = "is-default"; // 19
    constexpr static const char* KEY_IS_FORCED_SUBTITLE = "is-forced-subtitle"; // 19
    constexpr static const char* KEY_I_FRAME_INTERVAL = "i-frame-interval";
    constexpr static const char* KEY_LANGUAGE = "language"; // 19
    constexpr static const char* KEY_MAX_HEIGHT = "max-height"; // 19
    constexpr static const char* KEY_MAX_INPUT_SIZE = "max-input-size";
    constexpr static const char* KEY_MAX_WIDTH = "max-width"; // 19
    constexpr static const char* KEY_MIME = "mime";
    constexpr static const char* KEY_PUSH_BLANK_BUFFERS_ON_STOP = "push-blank-buffers-on-shutdown"; // 19
    constexpr static const char* KEY_REPEAT_PREVIOUS_FRAME_AFTER = "repeat-previous-frame-after"; // 19
    constexpr static const char* KEY_SAMPLE_RATE = "sample-rate";
    constexpr static const char* KEY_WIDTH = "width";
};
} // namespace media
} // namespace android
} // namespace jmi
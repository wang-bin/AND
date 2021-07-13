/*
 * AND: Android Native Dev in Modern C++ based on JMI
 * Copyright (C) 2018-2021 Wang Bin - wbsecg1@gmail.com
 * https://github.com/wang-bin/AND
 * https://github.com/wang-bin/JMI
 * MIT License
 */

#pragma once
#include "jmi/jmi.h"

namespace jmi {
namespace android {
namespace media {
namespace AudioManager {
enum {
    STREAM_VOICE_CALL = 0,
    STREAM_SYSTEM = 1,
    STREAM_RING = 2,
    STREAM_MUSIC = 3,
    STREAM_ALARM = 4,
    STREAM_NOTIFICATION = 5,
};
} // namespace AudioManager

namespace AudioFormat {
enum {
    CHANNEL_OUT_INVALID = 0x0,
    CHANNEL_OUT_DEFAULT = 0x1,
    CHANNEL_OUT_MONO = 0x4,
    CHANNEL_OUT_STEREO = 0xc,
    CHANNEL_OUT_QUAD = 0xcc,
    CHANNEL_OUT_SURROUND = 0x41c,
    CHANNEL_OUT_5POINT1 = 0xfc,
    CHANNEL_OUT_7POINT1 = 0x3fc,
    CHANNEL_OUT_FRONT_LEFT = 0x4,
    CHANNEL_OUT_FRONT_RIGHT = 0x8,
    CHANNEL_OUT_FRONT_CENTER = 0x10,
    CHANNEL_OUT_LOW_FREQUENCY = 0x20,
    CHANNEL_OUT_BACK_LEFT = 0x40,
    CHANNEL_OUT_BACK_RIGHT = 0x80,
    CHANNEL_OUT_BACK_CENTER = 0x400,
    CHANNEL_OUT_FRONT_LEFT_OF_CENTER = 0x100,
    CHANNEL_OUT_FRONT_RIGHT_OF_CENTER = 0x200,
    CHANNEL_OUT_SIDE_LEFT = 0x00000800, // api 21
    CHANNEL_OUT_SIDE_RIGHT = 0x00001000, // api 21
    CHANNEL_OUT_7POINT1_SURROUND = 0x000018fc, // api 23
    ENCODING_INVALID = 0x0,
    ENCODING_DEFAULT = 0x1,
    ENCODING_PCM_16BIT = 0x2,
    ENCODING_PCM_8BIT = 0x3,
    ENCODING_PCM_FLOAT = 0x4,
    ENCODING_AC3 = 0x5,
    ENCODING_E_AC3 = 0x6, // api21
    ENCODING_DTS = 0x7,
    ENCODING_IEC61937 = 0xd, // api24, hdmi|spdif, s16 stereo
    ENCODING_DOLBY_TRUEHD = 0xe,
};
} // namespace AudioFormat

class AudioTrack : public jmi::JObject<AudioTrack>
{
public:
    enum {
        MODE_STATIC = 0,
        MODE_STREAM = 1,
    };

    enum {
        STATE_UNINITIALIZED = 0x0,
        STATE_INITIALIZED = 0x1,
        STATE_NO_STATIC_DATA = 0x2,
    };

    enum {
        WRITE_BLOCKING     = 0,
        WRITE_NON_BLOCKING = 1,
    }; // not used

    using Base = jmi::JObject<AudioTrack>;
    using Base::Base; // inherits ctors
    static constexpr auto name() { return JMISTR("android/media/AudioTrack");} // required if derive from JObject<>
    static jfloat getMaxVolume();
    static jint getMinBufferSize(jint sampleRateInHz, jint channelConfig, jint audioFormat);

    void play();
    void stop();
    void pause();
    void flush();
    void release();
    jint getState() const;
    jint write(const jbyteArray data, jint offsetInBytes, jint sizeInBytes);
    jint write(const jshortArray data, jint offsetInShorts, jint sizeInShorts);
    // writeMode since api 21
    jint write(const jfloatArray data, jint offsetInFloats, jint sizeInFloats, jint writeMode);
    jint setVolume(jfloat gain); // api 21
    jint setStereoVolume(jfloat leftGain, jfloat rightGain);
};
} // namespace media
} // namespace android
} // namespace jmi
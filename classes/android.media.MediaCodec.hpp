/*
 * AND: Android Native Dev in Modern C++ based on JMI
 * Copyright (C) 2018-2021 Wang Bin - wbsecg1@gmail.com
 * https://github.com/wang-bin/AND
 * https://github.com/wang-bin/JMI
 * MIT License
 */

#pragma once
#include "android.media.MediaFormat.hpp"
#include "android.media.MediaCrypto.hpp"
#include "java.nio.ByteBuffer.hpp"

namespace jmi {
namespace android {
namespace view {
struct SurfaceTag : jmi::ClassTag { static constexpr auto name() { return JMISTR("android.view.Surface");}};
using Surface = JObject<SurfaceTag>;
} // namespace view
namespace media {
class MediaCodec : public jmi::JObject<MediaCodec> {
public:
    struct BufferInfo : public jmi::JObject<BufferInfo> {
        using Base = jmi::JObject<BufferInfo>;
        using Base::Base; // inherits ctors
        using jmi::JObject<BufferInfo>::create;
        static constexpr auto name() { return JMISTR("android/media/MediaCodec$BufferInfo");} // required if derive from JObject<>
        // DO NOT forget to call create()
        // fields, set to new value and returns the old value. value == nullptr gets old value only
        jint offset(jint* value = nullptr);
        jint size(jint* value = nullptr);
        jlong presentationTimeUs(jlong* value = nullptr);
        jint flags(jint* value = nullptr);
    };

    enum {
        BUFFER_FLAG_KEY_FRAME = 1, // api 21
        BUFFER_FLAG_CODEC_CONFIG = 2,
        BUFFER_FLAG_END_OF_STREAM = 4,
        BUFFER_FLAG_PARTIAL_FRAME = 8, // api 26

        CONFIGURE_FLAG_ENCODE = 1,

        INFO_OUTPUT_BUFFERS_CHANGED = -3,
        INFO_OUTPUT_FORMAT_CHANGED = -2,
        INFO_TRY_AGAIN_LATER = -1,
    };

    using Base = jmi::JObject<MediaCodec>;
    using Base::Base; // inherits ctors
    static constexpr auto name() { return JMISTR("android/media/MediaCodec");} // required if derive from JObject<>
    static MediaCodec createDecoderByType(const char* type);
    static MediaCodec createEncoderByType(const char* type);
    static MediaCodec createByCodecName(const char* name);

    void release();
    void configure(const MediaFormat &format, const view::Surface &surface, const MediaCrypto &crypto, jint flags);
    void start();
    void stop();
    void flush();
    std::string getName() const; // api 18
    void signalEndOfInputStream(); //api18
    MediaFormat getOutputFormat() const; // never returns null
    MediaFormat getInputFormat() const; // api 21. call after configure() to get accepted format
    void queueInputBuffer(jint index, jint offset, jint size, jlong presentationTimeUs, jint flags);
    //void queueSecureInputBuffer(jint index, jint offset, const CJNIMediaCodecCryptoInfo &info, jlong presentationTimeUs, jint flags);
    // return: index or -1
    jint dequeueInputBuffer(jlong timeoutUs);
    // return: index or INFO_*
    // info is create by user, and it's fields are changed by jni
    jint dequeueOutputBuffer(BufferInfo& info, jlong timeoutUs);
    jint dequeueOutputBuffer(std::reference_wrapper<BufferInfo> info, jlong timeoutUs);
    void releaseOutputBuffer(jint index, jboolean render);
    void releaseOutputBuffer(jint index, jlong renderTimestampNs); // api 21
    MediaFormat getOutputFormat(jint index) const; //api 21. call after configure() to get accepted format
    std::vector<java::nio::ByteBuffer> getInputBuffers() const; // Deprecated as of API 21
    std::vector<java::nio::ByteBuffer> getOutputBuffers() const; // Deprecated as of API 21
    java::nio::ByteBuffer getInputBuffer(jint index) const; // API 21+
    java::nio::ByteBuffer getOutputBuffer(jint index) const; // API 21+
    void setVideoScalingMode(jint mode);
    //void setParameters(Bundle params); // api21
    //void setInputSurface(Surface surface); //api23
    //void setOutputSurface(Surface surface); //api23
};

} // namespace media
} // namespace android
} // namespace jmi
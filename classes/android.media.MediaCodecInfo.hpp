/*
 * AND: Android Native Dev in Modern C++ based on JMI
 * Copyright (C) 2018-2021 Wang Bin - wbsecg1@gmail.com
 * https://github.com/wang-bin/AND
 * https://github.com/wang-bin/JMI
 * MIT License
 */
#pragma once
#include "jmi/jmi.h"
#include "android.media.MediaFormat.hpp"
#include <vector>

namespace jmi {
namespace android {
namespace media {
class MediaCodecInfo final: public jmi::JObject<MediaCodecInfo> { // inherits JObject so that it can be a return type like primitive types
public:
    using Base = jmi::JObject<MediaCodecInfo>;
    using Base::Base; // inherits ctors
    static constexpr auto name() { return JMISTR("android/media/MediaCodecInfo");} // required if derive from JObject<>

    struct AudioCapabilities final: public jmi::JObject<AudioCapabilities> { // api21
        using Base = jmi::JObject<AudioCapabilities>;
        using Base::Base; // inherits ctors
        using jmi::JObject<AudioCapabilities>::create;
        static constexpr auto name() { return JMISTR("android/media/MediaCodecInfo$AudioCapabilities");} // required if derive from JObject<>
        jboolean isSampleRateSupported(jint sampleRate) const;
        jint getMaxInputChannelCount() const;
        std::vector<jint> getSupportedSampleRates() const;
    };

    struct VideoCapabilities final: public jmi::JObject<VideoCapabilities> { // api21
        using Base = jmi::JObject<VideoCapabilities>;
        using Base::Base; // inherits ctors
        using jmi::JObject<VideoCapabilities>::create;
        static constexpr auto name() { return JMISTR("android/media/MediaCodecInfo$VideoCapabilities");} // required if derive from JObject<>
        jboolean areSizeAndRateSupported(jint width, jint height, jdouble frameRate) const;
        jboolean isSizeSupported(jint width, jint height) const;
        jint getHeightAlignment() const;
        jint getWidthAlignment() const;
    };

    struct EncoderCapabilities final: public jmi::JObject<EncoderCapabilities> { // api21
        enum {
            BITRATE_MODE_CQ = 0,
            BITRATE_MODE_VBR = 1,
            BITRATE_MODE_CBR = 2,
        };
        using Base = jmi::JObject<EncoderCapabilities>;
        using Base::Base; // inherits ctors
        using jmi::JObject<EncoderCapabilities>::create;
        static constexpr auto name() { return JMISTR("android/media/MediaCodecInfo$EncoderCapabilities");} // required if derive from JObject<>
        jboolean isBitrateModeSupported(jint mode) const;
    };

    struct CodecProfileLevel final: jmi::JObject<CodecProfileLevel> { //api16
        using Base = jmi::JObject<CodecProfileLevel>;
        using Base::Base; // inherits ctors
        using jmi::JObject<CodecProfileLevel>::create;
        static constexpr auto name() { return JMISTR("android/media/MediaCodecInfo$CodecProfileLevel");} // required if derive from JObject<>
        enum { // static field
            AACObjectMain = 1,
            AACObjectLC = 2,
            AACObjectSSR = 3,
            AACObjectLTP = 4,
            AACObjectHE = 5,
            AACObjectScalable = 6,
            AACObjectERLC = 17,
            AACObjectERScalable = 20, // api26
            AACObjectLD = 23,
            AACObjectHE_PS = 29,
            AACObjectELD = 39,
            AACObjectXHE = 42, // api28

            AVCLevel1 = 1,
            AVCLevel1b = 2,
            AVCLevel11 = 4,
            AVCLevel12 = 8,
            AVCLevel13 = 16,
            AVCLevel2 = 32,
            AVCLevel21 = 64,
            AVCLevel22 = 128,
            AVCLevel3 = 256,
            AVCLevel31 = 512,
            AVCLevel32 = 1024,
            AVCLevel4 = 2048,
            AVCLevel41 = 4096,
            AVCLevel42 = 8192,
            AVCLevel5 = 16384,
            AVCLevel51 = 32768,
            AVCLevel52 = 65536, // api21
            AVCProfileBaseline = 1,
            AVCProfileMain = 2,
            AVCProfileExtended = 4,
            AVCProfileHigh = 8,
            AVCProfileHigh10 = 16,
            AVCProfileHigh422 = 32,
            AVCProfileHigh444 = 64,
            AVCProfileConstrainedBaseline = 65536, //api27
            AVCProfileConstrainedHigh = 524288, //api27

            DolbyVisionLevelHd24 = 1, //api24
            DolbyVisionLevelHd30 = 2, //api24
            DolbyVisionLevelFhd24 = 4, //api24
            DolbyVisionLevelFhd30 = 8, //api24
            DolbyVisionLevelFhd60 = 16, //api24
            DolbyVisionLevelUhd24 = 32, //api24
            DolbyVisionLevelUhd30 = 64, //api24
            DolbyVisionLevelUhd48 = 128,
            DolbyVisionLevelUhd60 = 256,
            DolbyVisionProfileDvavPer = 1,
            DolbyVisionProfileDvavPen = 2,
            DolbyVisionProfileDvheDer = 4,
            DolbyVisionProfileDvheDen = 8,
            DolbyVisionProfileDvheDtr = 16,
            DolbyVisionProfileDvheStn = 32,
            DolbyVisionProfileDvheDth = 64,
            DolbyVisionProfileDvheDtb = 128,
            DolbyVisionProfileDvheSt = 256,
            DolbyVisionProfileDvavSe = 512,

            H263Level10 = 1,
            H263Level20 = 2,
            H263Level30 = 4,
            H263Level40 = 8,
            H263Level45 = 16,
            H263Level50 = 32,
            H263Level60 = 64,
            H263Level70 = 128,
            H263ProfileBaseline = 1,
            H263ProfileH320Coding = 2,
            H263ProfileBackwardCompatible = 4,
            H263ProfileISWV2 = 8,
            H263ProfileISWV3 = 16,
            H263ProfileHighCompression = 32,
            H263ProfileInternet = 64,
            H263ProfileInterlace = 128,
            H263ProfileHighLatency = 256,
            // api21
            HEVCHighTierLevel1 = 2,
            HEVCHighTierLevel2 = 8,
            HEVCHighTierLevel21 = 32,
            HEVCHighTierLevel3 = 128,
            HEVCHighTierLevel31 = 512,
            HEVCHighTierLevel4 = 2048,
            HEVCHighTierLevel41 = 8192,
            HEVCHighTierLevel5 = 32768,
            HEVCHighTierLevel51 = 131072,
            HEVCHighTierLevel52 = 524288,
            HEVCHighTierLevel6 = 2097152,
            HEVCHighTierLevel61 = 8388608,
            HEVCHighTierLevel62 = 33554432,
            HEVCMainTierLevel1 = 1,
            HEVCMainTierLevel2 = 4,
            HEVCMainTierLevel21 = 16,
            HEVCMainTierLevel3 = 64,
            HEVCMainTierLevel31 = 256,
            HEVCMainTierLevel4 = 1024,
            HEVCMainTierLevel41 = 4096,
            HEVCMainTierLevel5 = 16384,
            HEVCMainTierLevel51 = 65536,
            HEVCMainTierLevel52 = 262144,
            HEVCMainTierLevel6 = 1048576,
            HEVCMainTierLevel61 = 4194304,
            HEVCMainTierLevel62 = 16777216,
            HEVCProfileMain = 1,
            HEVCProfileMain10 = 2,
            HEVCProfileMainStill = 4, //api28
            HEVCProfileMain10HDR10 = 4096, // api24

            MPEG2LevelLL = 0, //api23
            MPEG2LevelML = 1, //api23
            MPEG2LevelH14 = 2, // api23
            MPEG2LevelHL = 3, //api23
            MPEG2LevelHP = 4, //api24
            MPEG2ProfileSimple = 0, //api23
            MPEG2ProfileMain = 1, //api23
            MPEG2Profile422 = 2, //api23
            MPEG2ProfileSNR = 3, //api23
            MPEG2ProfileSpatial = 4, //api23
            MPEG2ProfileHigh = 5, //api23

            MPEG4Level0 = 1,
            MPEG4Level0b = 2,
            MPEG4Level1 = 4,
            MPEG4Level2 = 8,
            MPEG4Level3 = 16,
            MPEG4Level3b = 24,
            MPEG4Level4 = 32,
            MPEG4Level4a = 64,
            MPEG4Level5 = 128,
            MPEG4Level6 = 256,
            MPEG4ProfileSimple = 1,
            MPEG4ProfileSimpleScalable = 2,
            MPEG4ProfileCore = 4,
            MPEG4ProfileMain = 8,
            MPEG4ProfileNbit = 16,
            MPEG4ProfileScalableTexture = 32,
            MPEG4ProfileSimpleFace = 64,
            MPEG4ProfileSimpleFBA = 128,
            MPEG4ProfileHybrid = 512,
            MPEG4ProfileBasicAnimated = 256,
            MPEG4ProfileAdvancedRealTime = 1024,
            MPEG4ProfileCoreScalable = 2048,
            MPEG4ProfileAdvancedCoding = 4096,
            MPEG4ProfileAdvancedCore = 8192,
            MPEG4ProfileAdvancedScalable = 16384,
            MPEG4ProfileAdvancedSimple = 32768,

            VP8Level_Version0 = 1,
            VP8Level_Version1 = 2,
            VP8Level_Version2 = 4,
            VP8Level_Version3 = 8,
            VP8ProfileMain = 1,

            VP9Level1 = 1,
            VP9Level11 = 2,
            VP9Level2 = 4,
            VP9Level21 = 8,
            VP9Level3 = 16,
            VP9Level31 = 32,
            VP9Level4 = 64,
            VP9Level41 = 128,
            VP9Level5 = 256,
            VP9Level51 = 512,
            VP9Level52 = 1024,
            VP9Level6 = 2048,
            VP9Level61 = 4096,
            VP9Level62 = 8192,
            VP9Profile0 = 1,
            VP9Profile1 = 2,
            VP9Profile2 = 4,
            VP9Profile3 = 8,
            VP9Profile2HDR = 4096, //api24
            VP9Profile3HDR = 8192, //api24
        };
    // Fields
    //Defined in the OpenMAX IL specs, depending on the type of media this can be OMX_VIDEO_AVCLEVELTYPE, OMX_VIDEO_H263LEVELTYPE OMX_VIDEO_MPEG4LEVELTYPE, OMX_VIDEO_VP8LEVELTYPE or OMX_VIDEO_VP9LEVELTYPE
        jint level() const; // assume read only. return field<jint>("level").get();
    //Defined in the OpenMAX IL specs, depending on the type of media this can be OMX_VIDEO_AVCPROFILETYPE, OMX_VIDEO_H263PROFILETYPE, OMX_VIDEO_MPEG4PROFILETYPE, OMX_VIDEO_VP8PROFILETYPE or OMX_VIDEO_VP9PROFILETYPE
        jint profile() const; //return field<jint>("profile").get();
    };

    // nested classes
    class CodecCapabilities final: public jmi::JObject<CodecCapabilities> { // api16
    public:
        using Base = jmi::JObject<CodecCapabilities>;
        using Base::Base; // inherits ctors
        using jmi::JObject<CodecCapabilities>::create;
        static constexpr auto name() { return JMISTR("android/media/MediaCodecInfo$CodecCapabilities");} // required if derive from JObject<>
        static CodecCapabilities createFromProfileLevel(const char* mime, jint profile, jint level); //api21

        // api21: getXXXCapabilities()
        AudioCapabilities getAudioCapabilities() const;
        EncoderCapabilities getEncoderCapabilities() const;
        VideoCapabilities getVideoCapabilities() const;

        MediaFormat getDefaultFormat() const; // api21
        jint getMaxSupportedInstances() const; // api23. not all devices returns a correct value, e.g. Samsung p600
        std::string getMimeType() const;
        jboolean isFeatureRequired(const char* name) const; // api21
        jboolean isFeatureSupported(const char* name) const; // api19
        jboolean isFormatSupported(MediaFormat format) const; //api21
    // public fields
    //Defined in the OpenMAX IL specs, color format values are drawn from OMX_COLOR_FORMATTYPE
        std::vector<jint> colorFormats() const; // assume read only.  return field<std::vector<jint>>("colorFormats").get();
        std::vector<CodecProfileLevel> profileLevels() const; //return field<std::vector<CodecProfileLevel>>("profileLevels").get();
    };

    CodecCapabilities getCapabilitiesForType(const char* type) const;
    std::string getName() const;
    std::vector<std::string> getSupportedTypes() const;
    jboolean isEncoder() const;
protected:
    // create
};
} // namespace media
} // namespace android
} // namespace jmi
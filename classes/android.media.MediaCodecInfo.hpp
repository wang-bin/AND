/*
 * AND: Android Native Dev in Modern C++ based on JMI
 * Copyright (C) 2018-2019 Wang Bin - wbsecg1@gmail.com
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
class MediaCodecInfo : public jmi::JObject<MediaCodecInfo> { // inherits JObject so that it can be a return type like primitive types
public:
    using Base = jmi::JObject<MediaCodecInfo>;
    using Base::Base; // inherits ctors
    static std::string name() { return "android/media/MediaCodecInfo";} // required if derive from JObject<>

    struct CodecProfileLevel : jmi::JObject<CodecProfileLevel> {
        using Base = jmi::JObject<CodecProfileLevel>;
        using Base::Base; // inherits ctors
        using jmi::JObject<CodecProfileLevel>::create;
        static std::string name() { return "android/media/MediaCodecInfo$CodecProfileLevel";} // required if derive from JObject<>
        enum { // static field
            AACObjectELD = 39,
            AACObjectERLC = 17,
            AACObjectERScalable = 20, // api26
            AACObjectHE = 5,
            AACObjectHE_PS = 29,
            AACObjectLC = 2,
            AACObjectLD = 23,
            AACObjectLTP = 4,
            AACObjectMain = 1,
            AACObjectSSR = 3,
            AACObjectScalable = 6,
            AACObjectXHE = 42, // api28
            AVCLevel1 = 1,
            AVCLevel11 = 4,
            AVCLevel12 = 8,
            AVCLevel13 = 16,
            AVCLevel1b = 2,
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
            AVCProfileConstrainedBaseline = 65536, //api27
            AVCProfileConstrainedHigh = 524288, //api27
            AVCProfileExtended = 4,
            AVCProfileHigh = 8,
            AVCProfileHigh10 = 16,
            AVCProfileHigh422 = 32,
            AVCProfileHigh444 = 64,
            AVCProfileMain = 2,
            DolbyVisionLevelFhd24 = 4, //api24
            DolbyVisionLevelFhd30 = 8, //api24
            DolbyVisionLevelFhd60 = 16, //api24
            DolbyVisionLevelHd24 = 1, //api24
            DolbyVisionLevelHd30 = 2, //api24
            DolbyVisionLevelUhd24 = 32, //api24
            DolbyVisionLevelUhd30 = 64, //api24
            DolbyVisionLevelUhd48 = 128,
            DolbyVisionLevelUhd60 = 256,
            DolbyVisionProfileDvavPen = 2,
            DolbyVisionProfileDvavPer = 1,
            DolbyVisionProfileDvavSe = 512,
            DolbyVisionProfileDvheDen = 8,
            DolbyVisionProfileDvheDer = 4,
            DolbyVisionProfileDvheDtb = 128,
            DolbyVisionProfileDvheDth = 64,
            DolbyVisionProfileDvheDtr = 16,
            DolbyVisionProfileDvheSt = 256,
            DolbyVisionProfileDvheStn = 32,
            H263Level10 = 1,
            H263Level20 = 2,
            H263Level30 = 4,
            H263Level40 = 8,
            H263Level45 = 16,
            H263Level50 = 32,
            H263Level60 = 64,
            H263Level70 = 128,
            H263ProfileBackwardCompatible = 4,
            H263ProfileBaseline = 1,
            H263ProfileH320Coding = 2,
            H263ProfileHighCompression = 32,
            H263ProfileHighLatency = 256,
            H263ProfileISWV2 = 8,
            H263ProfileISWV3 = 16,
            H263ProfileInterlace = 128,
            H263ProfileInternet = 64,
            // api21
            HEVCHighTierLevel1 = 2,
            HEVCHighTierLevel2 = 8,
            HEVCHighTierLevel21 = 32,
            HEVCHighTierLevel3 = 128,
            HEVCMainTierLevel31 = 256,
            HEVCHighTierLevel31 = 512,
            HEVCMainTierLevel21 = 16,
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
            HEVCMainTierLevel3 = 64,
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
            HEVCProfileMain10HDR10 = 4096, // api24
            HEVCProfileMainStill = 4, //api28
            MPEG2LevelH14 = 2, // api23
            MPEG2LevelHL = 3, //api23
            MPEG2LevelHP = 4, //api24
            MPEG2LevelLL = 0, //api23
            MPEG2LevelML = 1, //api23
            MPEG2Profile422 = 2, //api23
            MPEG2ProfileHigh = 5, //api23
            MPEG2ProfileMain = 1, //api23
            MPEG2ProfileSNR = 3, //api23
            MPEG2ProfileSimple = 0, //api23
            MPEG2ProfileSpatial = 4, //api23
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
            MPEG4ProfileAdvancedCoding = 4096,
            MPEG4ProfileAdvancedCore = 8192,
            MPEG4ProfileAdvancedRealTime = 1024,
            MPEG4ProfileAdvancedScalable = 16384,
            MPEG4ProfileAdvancedSimple = 32768,
            MPEG4ProfileBasicAnimated = 256,
            MPEG4ProfileCore = 4,
            MPEG4ProfileCoreScalable = 2048,
            MPEG4ProfileHybrid = 512,
            MPEG4ProfileMain = 8,
            MPEG4ProfileNbit = 16,
            MPEG4ProfileScalableTexture = 32,
            MPEG4ProfileSimple = 1,
            MPEG4ProfileSimpleFBA = 128,
            MPEG4ProfileSimpleFace = 64,
            MPEG4ProfileSimpleScalable = 2,
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
            VP9Profile2HDR = 4096, //api24
            VP9Profile3 = 8,
            VP9Profile3HDR = 8192, //api24
        };
    // Fields
    //Defined in the OpenMAX IL specs, depending on the type of media this can be OMX_VIDEO_AVCLEVELTYPE, OMX_VIDEO_H263LEVELTYPE OMX_VIDEO_MPEG4LEVELTYPE, OMX_VIDEO_VP8LEVELTYPE or OMX_VIDEO_VP9LEVELTYPE
        jint level() const; // assume read only. return field<jint>("level").get();
    //Defined in the OpenMAX IL specs, depending on the type of media this can be OMX_VIDEO_AVCPROFILETYPE, OMX_VIDEO_H263PROFILETYPE, OMX_VIDEO_MPEG4PROFILETYPE, OMX_VIDEO_VP8PROFILETYPE or OMX_VIDEO_VP9PROFILETYPE
        jint profile() const; //return field<jint>("profile").get();
    };

    // nested classes
    class CodecCapabilities : public jmi::JObject<CodecCapabilities> {
    public:
        using Base = jmi::JObject<CodecCapabilities>;
        using Base::Base; // inherits ctors
        using jmi::JObject<CodecCapabilities>::create;
        static std::string name() { return "android/media/MediaCodecInfo$CodecCapabilities";} // required if derive from JObject<>
        static CodecCapabilities createFromProfileLevel(const char* mime, jint profile, jint level);
        //AudioCapabilities getAudioCapabilities() const;
        MediaFormat getDefaultFormat() const;
        //EncoderCapabilities getEncoderCapabilities() const;
        jint getMaxSupportedInstances() const;
        std::string getMimeType() const;
        //VideoCapabilities getVideoCapabilities() const;
        jboolean isFeatureRequired(const char* name) const;
        jboolean isFeatureSupported(const char* name) const;
        jboolean isFormatSupported(MediaFormat format) const;
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
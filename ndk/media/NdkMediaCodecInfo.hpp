/*
 * AND: Android Native Dev in Modern C++ based on JMI
 * Copyright (C) 2018-2026 Wang Bin - wbsecg1@gmail.com
 * https://github.com/wang-bin/AND
 * https://github.com/wang-bin/JMI
 * MIT License
 */

#pragma once

#include "NdkMediaError.hpp"
#include <stddef.h>
#include <stdint.h>
#include "NdkMediaFormat.hpp"

NDKMEDIA_NS_BEGIN

struct ACodecAudioCapabilities;
typedef struct ACodecAudioCapabilities ACodecAudioCapabilities;
struct ACodecVideoCapabilities;
typedef struct ACodecVideoCapabilities ACodecVideoCapabilities;
struct ACodecEncoderCapabilities;
typedef struct ACodecEncoderCapabilities ACodecEncoderCapabilities;
struct AMediaCodecInfo;
typedef struct AMediaCodecInfo AMediaCodecInfo;

typedef struct AIntRange {
	int32_t mLower;
	int32_t mUpper;
} AIntRange;

typedef struct ADoubleRange {
	double mLower;
	double mUpper;
} ADoubleRange;

typedef enum AMediaCodecKind : int32_t {
	AMediaCodecKind_INVALID = 0,
	AMediaCodecKind_DECODER = 1,
	AMediaCodecKind_ENCODER = 2,
} AMediaCodecKind;

typedef enum AMediaCodecType : int32_t {
	AMediaCodecType_INVALID_CODEC_INFO = 0,
	AMediaCodecType_SOFTWARE_ONLY = 1,
	AMediaCodecType_HARDWARE_ACCELERATED = 2,
	AMediaCodecType_SOFTWARE_WITH_DEVICE_ACCESS = 3,
} AMediaCodecType;

typedef enum ABitrateMode : int32_t {
	ABITRATE_MODE_CQ = 0,
	ABITRATE_MODE_VBR = 1,
	ABITRATE_MODE_CBR = 2,
	ABITRATE_MODE_CBR_FD = 3,
} ABitrateMode;

const char* _Nullable AMediaCodecInfo_getCanonicalName(const AMediaCodecInfo* _Nonnull info);
AMediaCodecKind AMediaCodecInfo_getKind(const AMediaCodecInfo* _Nonnull info);
int32_t AMediaCodecInfo_isVendor(const AMediaCodecInfo* _Nonnull info);
AMediaCodecType AMediaCodecInfo_getMediaCodecInfoType(const AMediaCodecInfo* _Nonnull info);
const char* _Nullable AMediaCodecInfo_getMediaType(const AMediaCodecInfo* _Nonnull info);
int32_t AMediaCodecInfo_getMaxSupportedInstances(const AMediaCodecInfo* _Nonnull info);
int32_t AMediaCodecInfo_isFeatureSupported(const AMediaCodecInfo* _Nonnull info, const char* _Nonnull featureName);
int32_t AMediaCodecInfo_isFeatureRequired(const AMediaCodecInfo* _Nonnull info, const char* _Nonnull featureName);
int32_t AMediaCodecInfo_isFormatSupported(const AMediaCodecInfo* _Nonnull info, const AMediaFormat* _Nonnull format);
media_status_t AMediaCodecInfo_getAudioCapabilities(const AMediaCodecInfo* _Nonnull info, const ACodecAudioCapabilities* _Nullable * _Nonnull outAudioCaps);
media_status_t AMediaCodecInfo_getVideoCapabilities(const AMediaCodecInfo* _Nonnull info, const ACodecVideoCapabilities* _Nullable * _Nonnull outVideoCaps);
media_status_t AMediaCodecInfo_getEncoderCapabilities(const AMediaCodecInfo* _Nonnull info, const ACodecEncoderCapabilities* _Nullable * _Nonnull outEncoderCaps);

media_status_t ACodecAudioCapabilities_getBitrateRange(const ACodecAudioCapabilities* _Nonnull audioCaps, AIntRange* _Nonnull outRange);
media_status_t ACodecAudioCapabilities_getSupportedSampleRates(const ACodecAudioCapabilities* _Nonnull audioCaps, const int* _Nullable * _Nonnull outArrayPtr, size_t* _Nonnull outCount);
media_status_t ACodecAudioCapabilities_getSupportedSampleRateRanges(const ACodecAudioCapabilities* _Nonnull audioCaps, const AIntRange* _Nullable * _Nonnull outArrayPtr, size_t* _Nonnull outCount);
int32_t ACodecAudioCapabilities_getMaxInputChannelCount(const ACodecAudioCapabilities* _Nonnull audioCaps);
int32_t ACodecAudioCapabilities_getMinInputChannelCount(const ACodecAudioCapabilities* _Nonnull audioCaps);
media_status_t ACodecAudioCapabilities_getInputChannelCountRanges(const ACodecAudioCapabilities* _Nonnull audioCaps, const AIntRange* _Nullable * _Nonnull outArrayPtr, size_t* _Nonnull outCount);
int32_t ACodecAudioCapabilities_isSampleRateSupported(const ACodecAudioCapabilities* _Nonnull audioCaps, int32_t sampleRate);

media_status_t ACodecVideoCapabilities_getBitrateRange(const ACodecVideoCapabilities* _Nonnull videoCaps, AIntRange* _Nonnull outRange);
media_status_t ACodecVideoCapabilities_getSupportedWidths(const ACodecVideoCapabilities* _Nonnull videoCaps, AIntRange* _Nonnull outRange);
media_status_t ACodecVideoCapabilities_getSupportedHeights(const ACodecVideoCapabilities* _Nonnull videoCaps, AIntRange* _Nonnull outRange);
int32_t ACodecVideoCapabilities_getWidthAlignment(const ACodecVideoCapabilities* _Nonnull videoCaps);
int32_t ACodecVideoCapabilities_getHeightAlignment(const ACodecVideoCapabilities* _Nonnull videoCaps);
media_status_t ACodecVideoCapabilities_getSupportedFrameRates(const ACodecVideoCapabilities* _Nonnull videoCaps, AIntRange* _Nonnull outRange);
media_status_t ACodecVideoCapabilities_getSupportedWidthsFor(const ACodecVideoCapabilities* _Nonnull videoCaps, int32_t height, AIntRange* _Nonnull outRange);
media_status_t ACodecVideoCapabilities_getSupportedHeightsFor(const ACodecVideoCapabilities* _Nonnull videoCaps, int32_t width, AIntRange* _Nonnull outRange);
media_status_t ACodecVideoCapabilities_getSupportedFrameRatesFor(const ACodecVideoCapabilities* _Nonnull videoCaps, int32_t width, int32_t height, ADoubleRange* _Nonnull outRange);
media_status_t ACodecVideoCapabilities_getAchievableFrameRatesFor(const ACodecVideoCapabilities* _Nonnull videoCaps, int32_t width, int32_t height, ADoubleRange* _Nonnull outRange);
int32_t ACodecVideoCapabilities_areSizeAndRateSupported(const ACodecVideoCapabilities* _Nonnull videoCaps, int32_t width, int32_t height, double frameRate);
int32_t ACodecVideoCapabilities_isSizeSupported(const ACodecVideoCapabilities* _Nonnull videoCaps, int32_t width, int32_t height);

media_status_t ACodecEncoderCapabilities_getQualityRange(const ACodecEncoderCapabilities* _Nonnull encoderCaps, AIntRange* _Nonnull outRange);
media_status_t ACodecEncoderCapabilities_getComplexityRange(const ACodecEncoderCapabilities* _Nonnull encoderCaps, AIntRange* _Nonnull outRange);
int32_t ACodecEncoderCapabilities_isBitrateModeSupported(const ACodecEncoderCapabilities* _Nonnull encoderCaps, ABitrateMode mode);

extern const char* _Nonnull AMediaCodecInfo_FEATURE_AdaptivePlayback;
extern const char* _Nonnull AMediaCodecInfo_FEATURE_SecurePlayback;
extern const char* _Nonnull AMediaCodecInfo_FEATURE_TunneledPlayback;
extern const char* _Nonnull AMediaCodecInfo_FEATURE_DynamicTimestamp;

NDKMEDIA_NS_END

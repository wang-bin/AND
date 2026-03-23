/*
 * AND: Android Native Dev in Modern C++ based on JMI
 * Copyright (C) 2018-2026 Wang Bin - wbsecg1@gmail.com
 * https://github.com/wang-bin/AND
 * https://github.com/wang-bin/JMI
 * MIT License
 */

#pragma once

#include "../../classes/android.media.MediaCodecInfo.hpp"
#include "NdkMediaCodecInfo.hpp"
#include <string>
#include <vector>

NDKMEDIA_NS_BEGIN

struct ACodecAudioCapabilities {
	const ACodecAudioCapabilities* ndk_ = nullptr;
	jmi::android::media::MediaCodecInfo::AudioCapabilities jni_;
	std::vector<int32_t> sample_rates_;
	std::vector<AIntRange> sample_rate_ranges_;
	std::vector<AIntRange> channel_count_ranges_;
};

ACodecAudioCapabilities* fromNdk(ACodecAudioCapabilities* obj);
ACodecAudioCapabilities* toNdk(const ACodecAudioCapabilities* obj);


struct ACodecVideoCapabilities {
	const ACodecVideoCapabilities* ndk_ = nullptr;
	jmi::android::media::MediaCodecInfo::VideoCapabilities jni_;
};

ACodecVideoCapabilities* fromNdk(ACodecVideoCapabilities* obj);
ACodecVideoCapabilities* toNdk(const ACodecVideoCapabilities* obj);

struct ACodecEncoderCapabilities {
	const ACodecEncoderCapabilities* ndk_ = nullptr;
	jmi::android::media::MediaCodecInfo::EncoderCapabilities jni_;
};

ACodecEncoderCapabilities* fromNdk(ACodecEncoderCapabilities* obj);
ACodecEncoderCapabilities* toNdk(const ACodecEncoderCapabilities* obj);

struct AMediaCodecInfo {
	const AMediaCodecInfo* ndk_ = nullptr;
	jmi::android::media::MediaCodecInfo jni_;
	jmi::android::media::MediaCodecInfo::CodecCapabilities caps_;
	std::string canonical_name_;
	std::string media_type_;
	//union {
		ACodecAudioCapabilities audio_caps_;
		ACodecVideoCapabilities video_caps_;
	//};
	ACodecEncoderCapabilities encoder_caps_;
};

AMediaCodecInfo* fromNdk(AMediaCodecInfo* obj);
AMediaCodecInfo* toNdk(const AMediaCodecInfo* obj);

NDKMEDIA_NS_END

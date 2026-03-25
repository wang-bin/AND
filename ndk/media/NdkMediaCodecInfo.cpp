/*
 * AND: Android Native Dev in Modern C++ based on JMI
 * Copyright (C) 2026 Wang Bin - wbsecg1@gmail.com
 * https://github.com/wang-bin/AND
 * https://github.com/wang-bin/JMI
 * MIT License
 */

#include "NdkMediaCodecInfo.hpp"
#include "NdkMedia.h"
#include "NdkMediaCodecInfoPriv.hpp"
#include <dlfcn.h>
#include <iostream>
#include <utility>

NDKMEDIA_NS_BEGIN
using namespace std;
using namespace jmi;

extern const android::media::MediaFormat& toJmi(const AMediaFormat* obj);
extern AMediaFormat* toNdk(const AMediaFormat* obj);

ACodecAudioCapabilities* fromNdk(ACodecAudioCapabilities* obj)
{
	return new ACodecAudioCapabilities{obj};
}

ACodecAudioCapabilities* toNdk(const ACodecAudioCapabilities* obj)
{
	return obj ? const_cast<ACodecAudioCapabilities*>(obj->ndk_) : nullptr;
}

ACodecVideoCapabilities* fromNdk(ACodecVideoCapabilities* obj)
{
	return new ACodecVideoCapabilities{obj};
}

ACodecVideoCapabilities* toNdk(const ACodecVideoCapabilities* obj)
{
	return obj ? const_cast<ACodecVideoCapabilities*>(obj->ndk_) : nullptr;
}

ACodecEncoderCapabilities* fromNdk(ACodecEncoderCapabilities* obj)
{
	return new ACodecEncoderCapabilities{obj};
}

ACodecEncoderCapabilities* toNdk(const ACodecEncoderCapabilities* obj)
{
	return obj ? const_cast<ACodecEncoderCapabilities*>(obj->ndk_) : nullptr;
}

AMediaCodecInfo* fromNdk(AMediaCodecInfo* obj)
{
	return new AMediaCodecInfo{obj};
}

AMediaCodecInfo* toNdk(const AMediaCodecInfo* obj)
{
	return obj ? const_cast<AMediaCodecInfo*>(obj->ndk_) : nullptr;
}

namespace {

const char* strOrNull(string& storage)
{
	return storage.empty() ? nullptr : storage.c_str();
}

static
const android::media::MediaCodecInfo::CodecCapabilities& getCodecCaps(const AMediaCodecInfo* info)
{
	static const android::media::MediaCodecInfo::CodecCapabilities dummy;
	if (!info)
		return dummy;
	if (info->caps_)
		return info->caps_;

	auto obj = const_cast<AMediaCodecInfo*>(info);
	if (obj->media_type_.empty()) {
		auto types = obj->jni_.getSupportedTypes();
		if (!obj->jni_.error().empty() || types.empty())
			return dummy;
		obj->media_type_ = std::move(types[0]);
	}
	obj->caps_ = obj->jni_.getCapabilitiesForType(obj->media_type_.c_str());
	if (!obj->jni_.error().empty())
		return dummy;
	return obj->caps_;
}

static
void refreshAudioCaches(ACodecAudioCapabilities* audio)
{
	if (!audio || !audio->jni_)
		return;
	audio->sample_rates_ = audio->jni_.getSupportedSampleRates();
	if (!audio->jni_.error().empty()) {
		clog << audio->jni_.error() << endl;
	}
	audio->sample_rate_ranges_.clear();
	const auto sr_ranges = audio->jni_.getSupportedSampleRateRanges();
	if (!audio->jni_.error().empty() || sr_ranges.empty()) {
		clog << audio->jni_.error() << endl;
	} else {
		audio->sample_rate_ranges_.reserve(sr_ranges.size());
		for (const auto& r : sr_ranges)
			audio->sample_rate_ranges_.emplace_back(r.getLower<jint>(), r.getUpper<jint>());
	}
	audio->channel_count_ranges_.clear();
	const auto channel_count_ranges = audio->jni_.getInputChannelCountRanges();
	if (!audio->jni_.error().empty() || channel_count_ranges.empty()) {
		clog << audio->jni_.error() << endl;
	} else {
		audio->channel_count_ranges_.reserve(channel_count_ranges.size());
		for (const auto& r : channel_count_ranges)
			audio->channel_count_ranges_.emplace_back(r.getLower<jint>(), r.getUpper<jint>());
	}
}

} // namespace

const char* AMediaCodecInfo_FEATURE_AdaptivePlayback = "adaptive-playback";
const char* AMediaCodecInfo_FEATURE_SecurePlayback = "secure-playback";
const char* AMediaCodecInfo_FEATURE_TunneledPlayback = "tunneled-playback";
const char* AMediaCodecInfo_FEATURE_DynamicTimestamp = "dynamic-timestamp";

const char* _Nullable AMediaCodecInfo_getCanonicalName(const AMediaCodecInfo* _Nonnull info)
{
	static const auto fp = (decltype(&AMediaCodecInfo_getCanonicalName))(mediandk_so() ? dlsym(mediandk_so(), __func__) : nullptr);
	if (fp)
		return fp(toNdk(info));
	if (!info)
		return nullptr;
	auto obj = const_cast<AMediaCodecInfo*>(info);
	obj->canonical_name_ = obj->jni_.getCanonicalName();
	if (!obj->jni_.error().empty()) {
		obj->canonical_name_.clear();
		clog << __func__ << " ERROR: " << obj->jni_.error() << endl;
	}
	return strOrNull(obj->canonical_name_);
}

AMediaCodecKind AMediaCodecInfo_getKind(const AMediaCodecInfo* _Nonnull info)
{
	static const auto fp = (decltype(&AMediaCodecInfo_getKind))(mediandk_so() ? dlsym(mediandk_so(), __func__) : nullptr);
	if (fp)
		return fp(toNdk(info));
	if (!info)
		return AMediaCodecKind_INVALID;
	const auto is_encoder = info->jni_.isEncoder();
	if (!info->jni_.error().empty())
		return AMediaCodecKind_INVALID;
	return is_encoder ? AMediaCodecKind_ENCODER : AMediaCodecKind_DECODER;
}

int32_t AMediaCodecInfo_isVendor(const AMediaCodecInfo* _Nonnull info)
{
	static const auto fp = (decltype(&AMediaCodecInfo_isVendor))(mediandk_so() ? dlsym(mediandk_so(), __func__) : nullptr);
	if (fp)
		return fp(toNdk(info));
	if (!info)
		return -1;
	const auto ret = info->jni_.isVendor();
	if (!info->jni_.error().empty())
		return -1;
	return ret;
}

AMediaCodecType AMediaCodecInfo_getMediaCodecInfoType(const AMediaCodecInfo* _Nonnull info)
{
	static const auto fp = (decltype(&AMediaCodecInfo_getMediaCodecInfoType))(mediandk_so() ? dlsym(mediandk_so(), __func__) : nullptr);
	if (fp)
		return fp(toNdk(info));
	if (!info)
		return AMediaCodecType_INVALID_CODEC_INFO;
	const auto software_only = info->jni_.isSoftwareOnly();
	if (!info->jni_.error().empty())
		return AMediaCodecType_INVALID_CODEC_INFO;
	if (software_only)
		return AMediaCodecType_SOFTWARE_ONLY;
	const auto hw = info->jni_.isHardwareAccelerated();
	if (!info->jni_.error().empty())
		return AMediaCodecType_INVALID_CODEC_INFO;
	return hw ? AMediaCodecType_HARDWARE_ACCELERATED : AMediaCodecType_SOFTWARE_WITH_DEVICE_ACCESS;
}

const char* _Nullable AMediaCodecInfo_getMediaType(const AMediaCodecInfo* _Nonnull info)
{
	static const auto fp = (decltype(&AMediaCodecInfo_getMediaType))(mediandk_so() ? dlsym(mediandk_so(), __func__) : nullptr);
	if (fp)
		return fp(toNdk(info));
	if (!info)
		return nullptr;
	auto obj = const_cast<AMediaCodecInfo*>(info);
	if (obj->media_type_.empty()) {
		auto types = obj->jni_.getSupportedTypes();
		if (!obj->jni_.error().empty() || types.empty())
			return nullptr;
		obj->media_type_ = std::move(types[0]);
	}
	return obj->media_type_.c_str();
}

int32_t AMediaCodecInfo_getMaxSupportedInstances(const AMediaCodecInfo* _Nonnull info)
{
	static const auto fp = (decltype(&AMediaCodecInfo_getMaxSupportedInstances))(mediandk_so() ? dlsym(mediandk_so(), __func__) : nullptr);
	if (fp)
		return fp(toNdk(info));
	decltype(auto) caps = getCodecCaps(info);
	if (!caps)
		return -1;
	const auto ret = caps.getMaxSupportedInstances();
	if (!caps.error().empty())
		return -1;
	return ret;
}

int32_t AMediaCodecInfo_isFeatureSupported(const AMediaCodecInfo* _Nonnull info, const char* _Nonnull featureName)
{
	static const auto fp = (decltype(&AMediaCodecInfo_isFeatureSupported))(mediandk_so() ? dlsym(mediandk_so(), __func__) : nullptr);
	if (fp)
		return fp(toNdk(info), featureName);
	if (!info || !featureName)
		return -1;
	decltype(auto) caps = getCodecCaps(info);
	if (!caps)
		return -1;
	const auto ret = caps.isFeatureSupported(featureName);
	if (!caps.error().empty())
		return -1;
	return ret;
}

int32_t AMediaCodecInfo_isFeatureRequired(const AMediaCodecInfo* _Nonnull info, const char* _Nonnull featureName)
{
	static const auto fp = (decltype(&AMediaCodecInfo_isFeatureRequired))(mediandk_so() ? dlsym(mediandk_so(), __func__) : nullptr);
	if (fp)
		return fp(toNdk(info), featureName);
	if (!info || !featureName)
		return -1;
	decltype(auto) caps = getCodecCaps(info);
	if (!caps)
		return -1;
	const auto ret = caps.isFeatureRequired(featureName);
	if (!caps.error().empty())
		return -1;
	return ret;
}

int32_t AMediaCodecInfo_isFormatSupported(const AMediaCodecInfo* _Nonnull info, const AMediaFormat* _Nonnull format)
{
	static const auto fp = (decltype(&AMediaCodecInfo_isFormatSupported))(mediandk_so() ? dlsym(mediandk_so(), __func__) : nullptr);
	if (fp)
		return fp(toNdk(info), toNdk(format));
	if (!info || !format)
		return -1;
	decltype(auto) caps = getCodecCaps(info);
	if (!caps)
		return -1;
	const auto ret = caps.isFormatSupported(toJmi(format));
	if (!caps.error().empty())
		return -1;
	return ret;
}

media_status_t AMediaCodecInfo_getAudioCapabilities(const AMediaCodecInfo* _Nonnull info, const ACodecAudioCapabilities* _Nullable * _Nonnull outAudioCaps)
{
	static const auto fp = (decltype(&AMediaCodecInfo_getAudioCapabilities))(mediandk_so() ? dlsym(mediandk_so(), __func__) : nullptr);
	if (fp) {
		const ACodecAudioCapabilities* ndk_out = nullptr;
		const auto ret = fp(toNdk(info), &ndk_out);
		if (ret == AMEDIA_OK && ndk_out) {
			auto obj = const_cast<AMediaCodecInfo*>(info);
			obj->audio_caps_.ndk_ = ndk_out;
			*outAudioCaps = &obj->audio_caps_;
		}
		return ret;
	}
	if (!info || !outAudioCaps)
		return AMEDIA_ERROR_INVALID_PARAMETER;
	decltype(auto) caps = getCodecCaps(info);
	if (!caps)
		return AMEDIA_ERROR_UNSUPPORTED;
	auto obj = const_cast<AMediaCodecInfo*>(info);
	obj->audio_caps_.ndk_ = nullptr;
	obj->audio_caps_.jni_ = caps.getAudioCapabilities();
	if (!caps.error().empty() || !obj->audio_caps_.jni_)
		return AMEDIA_ERROR_UNSUPPORTED;
	refreshAudioCaches(&obj->audio_caps_);
	*outAudioCaps = &obj->audio_caps_;
	return AMEDIA_OK;
}

media_status_t AMediaCodecInfo_getVideoCapabilities(const AMediaCodecInfo* _Nonnull info, const ACodecVideoCapabilities* _Nullable * _Nonnull outVideoCaps)
{
	static const auto fp = (decltype(&AMediaCodecInfo_getVideoCapabilities))(mediandk_so() ? dlsym(mediandk_so(), __func__) : nullptr);
	if (fp) {
		const ACodecVideoCapabilities* ndk_out = nullptr;
		const auto ret = fp(toNdk(info), &ndk_out);
		if (ret == AMEDIA_OK && ndk_out) {
			auto obj = const_cast<AMediaCodecInfo*>(info);
			obj->video_caps_.ndk_ = ndk_out;
			*outVideoCaps = &obj->video_caps_;
		}
		return ret;
	}
	if (!info || !outVideoCaps)
		return AMEDIA_ERROR_INVALID_PARAMETER;
	decltype(auto) caps = getCodecCaps(info);
	if (!caps)
		return AMEDIA_ERROR_UNSUPPORTED;
	auto obj = const_cast<AMediaCodecInfo*>(info);
	obj->video_caps_.ndk_ = nullptr;
	obj->video_caps_.jni_ = caps.getVideoCapabilities();
	if (!caps.error().empty() || !obj->video_caps_.jni_)
		return AMEDIA_ERROR_UNSUPPORTED;
	*outVideoCaps = &obj->video_caps_;
	return AMEDIA_OK;
}

media_status_t AMediaCodecInfo_getEncoderCapabilities(const AMediaCodecInfo* _Nonnull info, const ACodecEncoderCapabilities* _Nullable * _Nonnull outEncoderCaps)
{
	static const auto fp = (decltype(&AMediaCodecInfo_getEncoderCapabilities))(mediandk_so() ? dlsym(mediandk_so(), __func__) : nullptr);
	if (fp) {
		const ACodecEncoderCapabilities* ndk_out = nullptr;
		const auto ret = fp(toNdk(info), &ndk_out);
		if (ret == AMEDIA_OK && ndk_out) {
			auto obj = const_cast<AMediaCodecInfo*>(info);
			obj->encoder_caps_.ndk_ = ndk_out;
			*outEncoderCaps = &obj->encoder_caps_;
		}
		return ret;
	}
	if (!info || !outEncoderCaps)
		return AMEDIA_ERROR_INVALID_PARAMETER;
	decltype(auto) caps = getCodecCaps(info);
	if (!caps)
		return AMEDIA_ERROR_UNSUPPORTED;
	auto obj = const_cast<AMediaCodecInfo*>(info);
	obj->encoder_caps_.ndk_ = nullptr;
	obj->encoder_caps_.jni_ = caps.getEncoderCapabilities();
	if (!caps.error().empty() || !obj->encoder_caps_.jni_)
		return AMEDIA_ERROR_UNSUPPORTED;
	*outEncoderCaps = &obj->encoder_caps_;
	return AMEDIA_OK;
}

media_status_t ACodecAudioCapabilities_getBitrateRange(const ACodecAudioCapabilities* _Nonnull audioCaps, AIntRange* _Nonnull outRange)
{
	static const auto fp = (decltype(&ACodecAudioCapabilities_getBitrateRange))(mediandk_so() ? dlsym(mediandk_so(), __func__) : nullptr);
	if (fp)
		return fp(toNdk(audioCaps), outRange);
	if (!audioCaps || !outRange || !audioCaps->jni_)
		return AMEDIA_ERROR_INVALID_PARAMETER;
	const auto range = audioCaps->jni_.getBitrateRange();
	if (!audioCaps->jni_.error().empty() || !range) {
		clog << audioCaps->jni_.error() << endl;
		return AMEDIA_ERROR_UNSUPPORTED;
	}
	outRange->mLower = range.getLower<jint>();
	outRange->mUpper = range.getUpper<jint>();
	return AMEDIA_OK;
}

media_status_t ACodecAudioCapabilities_getSupportedSampleRates(const ACodecAudioCapabilities* _Nonnull audioCaps, const int* _Nullable * _Nonnull outArrayPtr, size_t* _Nonnull outCount)
{
	static const auto fp = (decltype(&ACodecAudioCapabilities_getSupportedSampleRates))(mediandk_so() ? dlsym(mediandk_so(), __func__) : nullptr);
	if (fp)
		return fp(toNdk(audioCaps), outArrayPtr, outCount);
	if (!audioCaps || !outArrayPtr || !outCount)
		return AMEDIA_ERROR_INVALID_PARAMETER;
	const auto obj = audioCaps;
	if (obj->sample_rates_.empty())
		return AMEDIA_ERROR_UNSUPPORTED;
	*outArrayPtr = reinterpret_cast<const int*>(obj->sample_rates_.data());
	*outCount = obj->sample_rates_.size();
	return AMEDIA_OK;
}

media_status_t ACodecAudioCapabilities_getSupportedSampleRateRanges(const ACodecAudioCapabilities* _Nonnull audioCaps, const AIntRange* _Nullable * _Nonnull outArrayPtr, size_t* _Nonnull outCount)
{
	static const auto fp = (decltype(&ACodecAudioCapabilities_getSupportedSampleRateRanges))(mediandk_so() ? dlsym(mediandk_so(), __func__) : nullptr);
	if (fp)
		return fp(toNdk(audioCaps), outArrayPtr, outCount);
	if (!audioCaps || !outArrayPtr || !outCount)
		return AMEDIA_ERROR_INVALID_PARAMETER;
	if (audioCaps->sample_rate_ranges_.empty())
		return AMEDIA_ERROR_UNSUPPORTED;
	*outArrayPtr = audioCaps->sample_rate_ranges_.data();
	*outCount = audioCaps->sample_rate_ranges_.size();
	return AMEDIA_OK;
}

int32_t ACodecAudioCapabilities_getMaxInputChannelCount(const ACodecAudioCapabilities* _Nonnull audioCaps)
{
	static const auto fp = (decltype(&ACodecAudioCapabilities_getMaxInputChannelCount))(mediandk_so() ? dlsym(mediandk_so(), __func__) : nullptr);
	if (fp)
		return fp(toNdk(audioCaps));
	if (!audioCaps || !audioCaps->jni_)
		return -1;
	const auto ret = audioCaps->jni_.getMaxInputChannelCount();
	if (!audioCaps->jni_.error().empty())
		return -1;
	return ret;
}

int32_t ACodecAudioCapabilities_getMinInputChannelCount(const ACodecAudioCapabilities* _Nonnull audioCaps)
{
	static const auto fp = (decltype(&ACodecAudioCapabilities_getMinInputChannelCount))(mediandk_so() ? dlsym(mediandk_so(), __func__) : nullptr);
	if (fp)
		return fp(toNdk(audioCaps));
	if (!audioCaps)
		return -1;
    const auto ret = audioCaps->jni_.getMinInputChannelCount();
    if (!audioCaps->jni_.error().empty())
        return -1;
	return ret;
}

media_status_t ACodecAudioCapabilities_getInputChannelCountRanges(const ACodecAudioCapabilities* _Nonnull audioCaps, const AIntRange* _Nullable * _Nonnull outArrayPtr, size_t* _Nonnull outCount)
{
	static const auto fp = (decltype(&ACodecAudioCapabilities_getInputChannelCountRanges))(mediandk_so() ? dlsym(mediandk_so(), __func__) : nullptr);
	if (fp)
		return fp(toNdk(audioCaps), outArrayPtr, outCount);
	if (!audioCaps || !outArrayPtr || !outCount)
		return AMEDIA_ERROR_INVALID_PARAMETER;
	if (audioCaps->channel_count_ranges_.empty())
		return AMEDIA_ERROR_UNSUPPORTED;
	*outArrayPtr = audioCaps->channel_count_ranges_.data();
	*outCount = audioCaps->channel_count_ranges_.size();
	return AMEDIA_OK;
}

int32_t ACodecAudioCapabilities_isSampleRateSupported(const ACodecAudioCapabilities* _Nonnull audioCaps, int32_t sampleRate)
{
	static const auto fp = (decltype(&ACodecAudioCapabilities_isSampleRateSupported))(mediandk_so() ? dlsym(mediandk_so(), __func__) : nullptr);
	if (fp)
		return fp(toNdk(audioCaps), sampleRate);
	if (!audioCaps || !audioCaps->jni_)
		return -1;
	const auto ret = audioCaps->jni_.isSampleRateSupported(sampleRate);
	if (!audioCaps->jni_.error().empty())
		return -1;
	return ret;
}

media_status_t ACodecVideoCapabilities_getBitrateRange(const ACodecVideoCapabilities* _Nonnull videoCaps, AIntRange* _Nonnull outRange)
{
	static const auto fp = (decltype(&ACodecVideoCapabilities_getBitrateRange))(mediandk_so() ? dlsym(mediandk_so(), __func__) : nullptr);
	if (fp)
		return fp(toNdk(videoCaps), outRange);
	if (!videoCaps || !outRange || !videoCaps->jni_)
		return AMEDIA_ERROR_INVALID_PARAMETER;
	const auto range = videoCaps->jni_.getBitrateRange();
	if (!videoCaps->jni_.error().empty() || !range) {
		clog << videoCaps->jni_.error() << endl;
		return AMEDIA_ERROR_UNSUPPORTED;
	}
	outRange->mLower = range.getLower<jint>();
	outRange->mUpper = range.getUpper<jint>();
	return AMEDIA_OK;
}

media_status_t ACodecVideoCapabilities_getSupportedWidths(const ACodecVideoCapabilities* _Nonnull videoCaps, AIntRange* _Nonnull outRange)
{
	static const auto fp = (decltype(&ACodecVideoCapabilities_getSupportedWidths))(mediandk_so() ? dlsym(mediandk_so(), __func__) : nullptr);
	if (fp)
		return fp(toNdk(videoCaps), outRange);
	if (!videoCaps || !outRange || !videoCaps->jni_)
		return AMEDIA_ERROR_INVALID_PARAMETER;
	const auto range = videoCaps->jni_.getSupportedWidths();
	if (!videoCaps->jni_.error().empty() || !range) {
		clog << videoCaps->jni_.error() << endl;
		return AMEDIA_ERROR_UNSUPPORTED;
	}
	outRange->mLower = range.getLower<jint>();
	outRange->mUpper = range.getUpper<jint>();
	return AMEDIA_OK;
}

media_status_t ACodecVideoCapabilities_getSupportedHeights(const ACodecVideoCapabilities* _Nonnull videoCaps, AIntRange* _Nonnull outRange)
{
	static const auto fp = (decltype(&ACodecVideoCapabilities_getSupportedHeights))(mediandk_so() ? dlsym(mediandk_so(), __func__) : nullptr);
	if (fp)
		return fp(toNdk(videoCaps), outRange);
	if (!videoCaps || !outRange || !videoCaps->jni_)
		return AMEDIA_ERROR_INVALID_PARAMETER;
	const auto range = videoCaps->jni_.getSupportedHeights();
	if (!videoCaps->jni_.error().empty() || !range) {
		clog << videoCaps->jni_.error() << endl;
		return AMEDIA_ERROR_UNSUPPORTED;
	}
	outRange->mLower = range.getLower<jint>();
	outRange->mUpper = range.getUpper<jint>();
	return AMEDIA_OK;
}

int32_t ACodecVideoCapabilities_getWidthAlignment(const ACodecVideoCapabilities* _Nonnull videoCaps)
{
	static const auto fp = (decltype(&ACodecVideoCapabilities_getWidthAlignment))(mediandk_so() ? dlsym(mediandk_so(), __func__) : nullptr);
	if (fp)
		return fp(toNdk(videoCaps));
	if (!videoCaps || !videoCaps->jni_)
		return -1;
	const auto ret = videoCaps->jni_.getWidthAlignment();
	if (!videoCaps->jni_.error().empty())
		return -1;
	return ret;
}

int32_t ACodecVideoCapabilities_getHeightAlignment(const ACodecVideoCapabilities* _Nonnull videoCaps)
{
	static const auto fp = (decltype(&ACodecVideoCapabilities_getHeightAlignment))(mediandk_so() ? dlsym(mediandk_so(), __func__) : nullptr);
	if (fp)
		return fp(toNdk(videoCaps));
	if (!videoCaps || !videoCaps->jni_)
		return -1;
	const auto ret = videoCaps->jni_.getHeightAlignment();
	if (!videoCaps->jni_.error().empty())
		return -1;
	return ret;
}

media_status_t ACodecVideoCapabilities_getSupportedFrameRates(const ACodecVideoCapabilities* _Nonnull videoCaps, AIntRange* _Nonnull outRange)
{
	static const auto fp = (decltype(&ACodecVideoCapabilities_getSupportedFrameRates))(mediandk_so() ? dlsym(mediandk_so(), __func__) : nullptr);
	if (fp)
		return fp(toNdk(videoCaps), outRange);
	if (!videoCaps || !outRange || !videoCaps->jni_)
		return AMEDIA_ERROR_INVALID_PARAMETER;
	const auto range = videoCaps->jni_.getSupportedFrameRates();
	if (!videoCaps->jni_.error().empty() || !range) {
		clog << videoCaps->jni_.error() << endl;
		return AMEDIA_ERROR_UNSUPPORTED;
	}
	outRange->mLower = range.getLower<jint>();
	outRange->mUpper = range.getUpper<jint>();
	return AMEDIA_OK;
}

media_status_t ACodecVideoCapabilities_getSupportedWidthsFor(const ACodecVideoCapabilities* _Nonnull videoCaps, int32_t height, AIntRange* _Nonnull outRange)
{
	static const auto fp = (decltype(&ACodecVideoCapabilities_getSupportedWidthsFor))(mediandk_so() ? dlsym(mediandk_so(), __func__) : nullptr);
	if (fp)
		return fp(toNdk(videoCaps), height, outRange);
	if (!videoCaps || !outRange || !videoCaps->jni_)
		return AMEDIA_ERROR_INVALID_PARAMETER;
	const auto range = videoCaps->jni_.getSupportedWidthsFor(height);
	if (!videoCaps->jni_.error().empty() || !range) {
		clog << videoCaps->jni_.error() << endl;
		return AMEDIA_ERROR_UNSUPPORTED;
	}
	outRange->mLower = range.getLower<jint>();
	outRange->mUpper = range.getUpper<jint>();
	return AMEDIA_OK;
}

media_status_t ACodecVideoCapabilities_getSupportedHeightsFor(const ACodecVideoCapabilities* _Nonnull videoCaps, int32_t width, AIntRange* _Nonnull outRange)
{
	static const auto fp = (decltype(&ACodecVideoCapabilities_getSupportedHeightsFor))(mediandk_so() ? dlsym(mediandk_so(), __func__) : nullptr);
	if (fp)
		return fp(toNdk(videoCaps), width, outRange);
	if (!videoCaps || !outRange || !videoCaps->jni_)
		return AMEDIA_ERROR_INVALID_PARAMETER;
	const auto range = videoCaps->jni_.getSupportedHeightsFor(width);
	if (!videoCaps->jni_.error().empty() || !range) {
		clog << videoCaps->jni_.error() << endl;
		return AMEDIA_ERROR_UNSUPPORTED;
	}
	outRange->mLower = range.getLower<jint>();
	outRange->mUpper = range.getUpper<jint>();
	return AMEDIA_OK;
}

media_status_t ACodecVideoCapabilities_getSupportedFrameRatesFor(const ACodecVideoCapabilities* _Nonnull videoCaps, int32_t width, int32_t height, ADoubleRange* _Nonnull outRange)
{
	static const auto fp = (decltype(&ACodecVideoCapabilities_getSupportedFrameRatesFor))(mediandk_so() ? dlsym(mediandk_so(), __func__) : nullptr);
	if (fp)
		return fp(toNdk(videoCaps), width, height, outRange);
	if (!videoCaps || !outRange || !videoCaps->jni_)
		return AMEDIA_ERROR_INVALID_PARAMETER;
	const auto range = videoCaps->jni_.getSupportedFrameRatesFor(width, height);
	if (!videoCaps->jni_.error().empty() || !range) {
		clog << videoCaps->jni_.error() << endl;
		return AMEDIA_ERROR_UNSUPPORTED;
	}
	outRange->mLower = range.getLower<jdouble>();
	outRange->mUpper = range.getUpper<jdouble>();
	return AMEDIA_OK;
}

media_status_t ACodecVideoCapabilities_getAchievableFrameRatesFor(const ACodecVideoCapabilities* _Nonnull videoCaps, int32_t width, int32_t height, ADoubleRange* _Nonnull outRange)
{
	static const auto fp = (decltype(&ACodecVideoCapabilities_getAchievableFrameRatesFor))(mediandk_so() ? dlsym(mediandk_so(), __func__) : nullptr);
	if (fp)
		return fp(toNdk(videoCaps), width, height, outRange);
	if (!videoCaps || !outRange || !videoCaps->jni_)
		return AMEDIA_ERROR_INVALID_PARAMETER;
	const auto range = videoCaps->jni_.getAchievableFrameRatesFor(width, height);
	if (!videoCaps->jni_.error().empty() || !range) {
		clog << videoCaps->jni_.error() << endl;
		return AMEDIA_ERROR_UNSUPPORTED;
	}
	outRange->mLower = range.getLower<jdouble>();
	outRange->mUpper = range.getUpper<jdouble>();
	return AMEDIA_OK;
}

int32_t ACodecVideoCapabilities_areSizeAndRateSupported(const ACodecVideoCapabilities* _Nonnull videoCaps, int32_t width, int32_t height, double frameRate)
{
	static const auto fp = (decltype(&ACodecVideoCapabilities_areSizeAndRateSupported))(mediandk_so() ? dlsym(mediandk_so(), __func__) : nullptr);
	if (fp)
		return fp(toNdk(videoCaps), width, height, frameRate);
	if (!videoCaps || !videoCaps->jni_)
		return -1;
	const auto ret = videoCaps->jni_.areSizeAndRateSupported(width, height, frameRate);
	if (!videoCaps->jni_.error().empty())
		return -1;
	return ret;
}

int32_t ACodecVideoCapabilities_isSizeSupported(const ACodecVideoCapabilities* _Nonnull videoCaps, int32_t width, int32_t height)
{
	static const auto fp = (decltype(&ACodecVideoCapabilities_isSizeSupported))(mediandk_so() ? dlsym(mediandk_so(), __func__) : nullptr);
	if (fp)
		return fp(toNdk(videoCaps), width, height);
	if (!videoCaps || !videoCaps->jni_)
		return -1;
	const auto ret = videoCaps->jni_.isSizeSupported(width, height);
	if (!videoCaps->jni_.error().empty())
		return -1;
	return ret;
}

media_status_t ACodecEncoderCapabilities_getQualityRange(const ACodecEncoderCapabilities* _Nonnull encoderCaps, AIntRange* _Nonnull outRange)
{
	static const auto fp = (decltype(&ACodecEncoderCapabilities_getQualityRange))(mediandk_so() ? dlsym(mediandk_so(), __func__) : nullptr);
	if (fp)
		return fp(toNdk(encoderCaps), outRange);
	if (!encoderCaps || !outRange || !encoderCaps->jni_)
		return AMEDIA_ERROR_INVALID_PARAMETER;
	const auto range = encoderCaps->jni_.getQualityRange();
	if (!encoderCaps->jni_.error().empty() || !range) {
		clog << encoderCaps->jni_.error() << endl;
		return AMEDIA_ERROR_UNSUPPORTED;
	}
	outRange->mLower = range.getLower<jint>();
	outRange->mUpper = range.getUpper<jint>();
	return AMEDIA_OK;
}

media_status_t ACodecEncoderCapabilities_getComplexityRange(const ACodecEncoderCapabilities* _Nonnull encoderCaps, AIntRange* _Nonnull outRange)
{
	static const auto fp = (decltype(&ACodecEncoderCapabilities_getComplexityRange))(mediandk_so() ? dlsym(mediandk_so(), __func__) : nullptr);
	if (fp)
		return fp(toNdk(encoderCaps), outRange);
	if (!encoderCaps || !outRange || !encoderCaps->jni_)
		return AMEDIA_ERROR_INVALID_PARAMETER;
	const auto range = encoderCaps->jni_.getComplexityRange();
	if (!encoderCaps->jni_.error().empty() || !range) {
		clog << encoderCaps->jni_.error() << endl;
		return AMEDIA_ERROR_UNSUPPORTED;
	}
	outRange->mLower = range.getLower<jint>();
	outRange->mUpper = range.getUpper<jint>();
	return AMEDIA_OK;
}

int32_t ACodecEncoderCapabilities_isBitrateModeSupported(const ACodecEncoderCapabilities* _Nonnull encoderCaps, ABitrateMode mode)
{
	static const auto fp = (decltype(&ACodecEncoderCapabilities_isBitrateModeSupported))(mediandk_so() ? dlsym(mediandk_so(), __func__) : nullptr);
	if (fp)
		return fp(toNdk(encoderCaps), mode);
	if (!encoderCaps || !encoderCaps->jni_)
		return -1;
	const auto ret = encoderCaps->jni_.isBitrateModeSupported(mode);
	if (!encoderCaps->jni_.error().empty())
		return -1;
	return ret;
}

NDKMEDIA_NS_END

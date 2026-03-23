/*
 * AND: Android Native Dev in Modern C++ based on JMI
 * Copyright (C) 2018-2026 Wang Bin - wbsecg1@gmail.com
 * https://github.com/wang-bin/AND
 * https://github.com/wang-bin/JMI
 * MIT License
 */

#include "NdkMediaCodecStore.hpp"
#include "NdkMediaCodecInfoPriv.hpp"
#include "NdkMedia.h"
#include "../../classes/android.media.MediaCodecList.hpp"
#include <dlfcn.h>
#include <map>
#include <mutex>
#include <string>
#include <vector>

NDKMEDIA_NS_BEGIN
using namespace std;
using namespace jmi;
using namespace jmi::android::media;
extern AMediaFormat* toNdk(const AMediaFormat* obj);

namespace {

struct Store {
	vector<AMediaCodecInfo> decoders; // build() once, then immutable => stable addresses
	vector<AMediaCodecInfo> encoders;
	vector<string> media_type_strings; // storage that mMediaType points into
	vector<AMediaCodecSupportedMediaType> media_types;

	// TODO: log
	void build() {
		android::media::MediaCodecList codecs;
		if (!codecs.create(android::media::MediaCodecList::ALL_CODECS)) // api21 ctor
			return;
		auto infos = codecs.getCodecInfos();
		if (infos.empty()) {// api < 21
			if (const auto n = MediaCodecList::getCodecCount()) {
                for (auto i = 0; i < n; ++i)
                    infos.push_back(MediaCodecList::getCodecInfoAt(i));
            } else {
                return;
            }
        }

		// TODO: don't use map, keep original order
		map<string, uint32_t> mime_modes;

		for (auto& jni : infos) {
			const bool is_enc = jni.isEncoder();
			if (!jni.error().empty())
				continue;
			const auto name = jni.getCanonicalName();
			if (!jni.error().empty())
				continue;
			if (const auto types = jni.getSupportedTypes(); !types.empty()) {
				for (const auto& type : types) {
					AMediaCodecInfo info;
					info.jni_ = jni;
					info.canonical_name_ = name;
					info.media_type_ = type;
					uint32_t flag = is_enc ? AMediaCodecSupportedMediaType::FLAG_ENCODER
										   : AMediaCodecSupportedMediaType::FLAG_DECODER;
					for (const auto& t : types)
						mime_modes[t] |= flag;
					(is_enc ? encoders : decoders).push_back(std::move(info));
				}
			}
		}

		// Build stable string storage first, then point into it.
		media_type_strings.reserve(mime_modes.size());
		for (const auto& [mime, _] : mime_modes)
			media_type_strings.emplace_back(mime);

		media_types.reserve(mime_modes.size());
		for (const auto& s : media_type_strings) {
			media_types.push_back({
                .mMediaType = s.c_str(),
                .mMode = mime_modes.at(s),
            });
		}
	}
};

static const Store& getStore()
{
	static Store s;
	static once_flag flag;
	call_once(flag, [] { s.build(); });
	return s;
}

// Returns a stable wrapper for an NDK-owned AMediaCodecInfo*: same NDK ptr → same wrapper ptr.
static const AMediaCodecInfo* fromNdkCached(const AMediaCodecInfo* ndk)
{
	if (!ndk)
		return nullptr;
	static mutex mtx;
	static map<const AMediaCodecInfo*, AMediaCodecInfo> cache;
	[[maybe_unused]] const scoped_lock __(mtx);
	auto& entry = cache[ndk];
	entry.ndk_ = ndk;
	return &entry;
}

// Iterate through |infos|, optionally filtered by format mime, starting after
// the codec pointed to by *outCodecInfo (nullptr = from the beginning).
static media_status_t findNext(
	const vector<AMediaCodecInfo>& infos,
	const AMediaFormat* _Nullable format,
	const AMediaCodecInfo* _Nullable * _Nonnull outCodecInfo)
{
	size_t start = 0;
	if (*outCodecInfo) {
		for (size_t i = 0; i < infos.size(); ++i) {
			if (&infos[i] == *outCodecInfo) {
				start = i + 1;
				break;
			}
		}
	}

	const char* mime = nullptr;
	if (format)
		AMediaFormat_getString(const_cast<AMediaFormat*>(format), AMEDIAFORMAT_KEY_MIME, &mime);

	for (size_t i = start; i < infos.size(); ++i) {
		const auto* info = &infos[i];
		if (!mime || info->media_type_ == mime) {
			*outCodecInfo = info;
			return AMEDIA_OK;
		}
	}

	*outCodecInfo = nullptr;
	return AMEDIA_ERROR_UNSUPPORTED;
}

} // namespace

media_status_t AMediaCodecStore_getSupportedMediaTypes(
	const AMediaCodecSupportedMediaType* _Nullable * _Nonnull outMediaTypes,
	size_t* _Nonnull outCount)
{
	static const auto fp = (decltype(&AMediaCodecStore_getSupportedMediaTypes))(mediandk_so() ? dlsym(mediandk_so(), __func__) : nullptr);
	if (fp)
		return fp(outMediaTypes, outCount);
	if (!outMediaTypes || !outCount)
		return AMEDIA_ERROR_INVALID_PARAMETER;
	const auto& store = getStore();
	if (store.media_types.empty()) {
		*outMediaTypes = nullptr;
		*outCount = 0;
		return AMEDIA_ERROR_UNSUPPORTED;
	}
	*outMediaTypes = store.media_types.data();
	*outCount = store.media_types.size();
	return AMEDIA_OK;
}

media_status_t AMediaCodecStore_findNextDecoderForFormat(
	const AMediaFormat* _Nullable format,
	const AMediaCodecInfo* _Nullable * _Nonnull outCodecInfo)
{
	static const auto fp = (decltype(&AMediaCodecStore_findNextDecoderForFormat))(mediandk_so() ? dlsym(mediandk_so(), __func__) : nullptr);
	if (fp) {
		const AMediaCodecInfo* ndk_out = *outCodecInfo ? toNdk(*outCodecInfo) : nullptr;
		const auto ret = fp(toNdk(format), &ndk_out);
		*outCodecInfo = fromNdkCached(ndk_out);
		return ret;
	}
	if (!outCodecInfo)
		return AMEDIA_ERROR_INVALID_PARAMETER;
	return findNext(getStore().decoders, format, outCodecInfo);
}

media_status_t AMediaCodecStore_findNextEncoderForFormat(
	const AMediaFormat* _Nullable format,
	const AMediaCodecInfo* _Nullable * _Nonnull outCodecInfo)
{
	static const auto fp = (decltype(&AMediaCodecStore_findNextEncoderForFormat))(mediandk_so() ? dlsym(mediandk_so(), __func__) : nullptr);
	if (fp) {
		const AMediaCodecInfo* ndk_out = *outCodecInfo ? toNdk(*outCodecInfo) : nullptr;
		const auto ret = fp(toNdk(format), &ndk_out);
		*outCodecInfo = fromNdkCached(ndk_out);
		return ret;
	}
	if (!outCodecInfo)
		return AMEDIA_ERROR_INVALID_PARAMETER;
	return findNext(getStore().encoders, format, outCodecInfo);
}

media_status_t AMediaCodecStore_getCodecInfo(
	const char* _Nonnull name,
	const AMediaCodecInfo* _Nullable * _Nonnull outCodecInfo)
{
	static const auto fp = (decltype(&AMediaCodecStore_getCodecInfo))(mediandk_so() ? dlsym(mediandk_so(), __func__) : nullptr);
	if (fp) {
		const AMediaCodecInfo* ndk_out = nullptr;
		const auto ret = fp(name, &ndk_out);
		*outCodecInfo = fromNdkCached(ndk_out);
		return ret;
	}
	if (!name || !outCodecInfo)
		return AMEDIA_ERROR_INVALID_PARAMETER;
	const auto& store = getStore();
	for (const auto infos : {&store.decoders, &store.encoders}) {
		for (const auto& info : *infos) {
			if (info.canonical_name_ == name) {
				*outCodecInfo = &info;
				return AMEDIA_OK;
			}
		}
	}
	*outCodecInfo = nullptr;
	return AMEDIA_ERROR_UNSUPPORTED;
}

NDKMEDIA_NS_END

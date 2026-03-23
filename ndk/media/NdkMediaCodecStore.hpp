/*
 * AND: Android Native Dev in Modern C++ based on JMI
 * Copyright (C) 2018-2026 Wang Bin - wbsecg1@gmail.com
 * https://github.com/wang-bin/AND
 * https://github.com/wang-bin/JMI
 * MIT License
 */

#pragma once

#include "NdkMediaError.hpp"
#include "NdkMediaCodecInfo.hpp"
#include "NdkMediaFormat.hpp"
#include <stddef.h>
#include <stdint.h>

NDKMEDIA_NS_BEGIN

typedef struct AMediaCodecSupportedMediaType {
	enum Mode : uint32_t {
		FLAG_DECODER = 1 << 0,
		FLAG_ENCODER = 1 << 1,
	};
	const char* _Nonnull mMediaType;
	uint32_t mMode;
} AMediaCodecSupportedMediaType;

media_status_t AMediaCodecStore_getSupportedMediaTypes(
	const AMediaCodecSupportedMediaType* _Nullable * _Nonnull outMediaTypes,
	size_t* _Nonnull outCount);

media_status_t AMediaCodecStore_findNextDecoderForFormat(
	const AMediaFormat* _Nullable format, // TODO: ndk _Nonnull, but comment says nullable
	const AMediaCodecInfo* _Nullable * _Nonnull outCodecInfo);

media_status_t AMediaCodecStore_findNextEncoderForFormat(
	const AMediaFormat* _Nullable format, // TODO: ndk _Nonnull, but comment says nullable
	const AMediaCodecInfo* _Nullable * _Nonnull outCodecInfo);

media_status_t AMediaCodecStore_getCodecInfo(
	const char* _Nonnull name,
	const AMediaCodecInfo* _Nullable * _Nonnull outCodecInfo);

NDKMEDIA_NS_END

/*
 * AND: Android Native Dev in Modern C++ based on JMI
 * Copyright (C) 2018 Wang Bin - wbsecg1@gmail.com
 * https://github.com/wang-bin/AND
 * https://github.com/wang-bin/JMI
 * MIT License
 */

#pragma once
#include "NdkMediaError.hpp"
#include <stdint.h>

NDKMEDIA_NS_BEGIN

struct AMediaFormat;
typedef struct AMediaFormat AMediaFormat;

AMediaFormat *AMediaFormat_new();
media_status_t AMediaFormat_delete(AMediaFormat*);
const char* AMediaFormat_toString(AMediaFormat*);
bool AMediaFormat_getInt32(AMediaFormat*, const char *name, int32_t *out);
bool AMediaFormat_getInt64(AMediaFormat*, const char *name, int64_t *out);
bool AMediaFormat_getFloat(AMediaFormat*, const char *name, float *out);
bool AMediaFormat_getBuffer(AMediaFormat*, const char *name, void** data, size_t *size);
bool AMediaFormat_getString(AMediaFormat*, const char *name, const char **out);
void AMediaFormat_setInt32(AMediaFormat*, const char* name, int32_t value);
void AMediaFormat_setInt64(AMediaFormat*, const char* name, int64_t value);
void AMediaFormat_setFloat(AMediaFormat*, const char* name, float value);
void AMediaFormat_setString(AMediaFormat*, const char* name, const char* value);
void AMediaFormat_setBuffer(AMediaFormat*, const char* name, void* data, size_t size);

// constexpr
extern const char* AMEDIAFORMAT_KEY_AAC_DRC_ATTENUATION_FACTOR;
extern const char* AMEDIAFORMAT_KEY_AAC_DRC_BOOST_FACTOR;
extern const char* AMEDIAFORMAT_KEY_AAC_DRC_HEAVY_COMPRESSION;
extern const char* AMEDIAFORMAT_KEY_AAC_DRC_TARGET_REFERENCE_LEVEL;
extern const char* AMEDIAFORMAT_KEY_AAC_ENCODED_TARGET_LEVEL;
extern const char* AMEDIAFORMAT_KEY_AAC_MAX_OUTPUT_CHANNEL_COUNT;
extern const char* AMEDIAFORMAT_KEY_AAC_PROFILE;
extern const char* AMEDIAFORMAT_KEY_AAC_SBR_MODE;
extern const char* AMEDIAFORMAT_KEY_AUDIO_SESSION_ID;
extern const char* AMEDIAFORMAT_KEY_BITRATE_MODE;
extern const char* AMEDIAFORMAT_KEY_BIT_RATE;
extern const char* AMEDIAFORMAT_KEY_CAPTURE_RATE;
extern const char* AMEDIAFORMAT_KEY_CHANNEL_COUNT;
extern const char* AMEDIAFORMAT_KEY_CHANNEL_MASK;
constexpr static  const char* AMEDIAFORMAT_KEY_COLOR_FORMAT = "color-format";
extern const char* AMEDIAFORMAT_KEY_COLOR_RANGE;
extern const char* AMEDIAFORMAT_KEY_COLOR_STANDARD;
extern const char* AMEDIAFORMAT_KEY_COLOR_TRANSFER;
extern const char* AMEDIAFORMAT_KEY_COMPLEXITY;
extern const char* AMEDIAFORMAT_KEY_CSD;
constexpr static const char* AMEDIAFORMAT_KEY_CSD_0 = "csd-0";
constexpr static const char* AMEDIAFORMAT_KEY_CSD_1 = "csd-1";
constexpr static const char* AMEDIAFORMAT_KEY_CSD_2 = "csd-2";
extern const char* AMEDIAFORMAT_KEY_DISPLAY_CROP;
extern const char* AMEDIAFORMAT_KEY_DISPLAY_HEIGHT;
extern const char* AMEDIAFORMAT_KEY_DISPLAY_WIDTH;
extern const char* AMEDIAFORMAT_KEY_DURATION;
extern const char* AMEDIAFORMAT_KEY_FLAC_COMPRESSION_LEVEL;
extern const char* AMEDIAFORMAT_KEY_FRAME_RATE;
extern const char* AMEDIAFORMAT_KEY_GRID_COLUMNS;
extern const char* AMEDIAFORMAT_KEY_GRID_ROWS;
extern const char* AMEDIAFORMAT_KEY_HDR_STATIC_INFO;
constexpr static const char* AMEDIAFORMAT_KEY_HEIGHT = "height";
extern const char* AMEDIAFORMAT_KEY_INTRA_REFRESH_PERIOD;
extern const char* AMEDIAFORMAT_KEY_IS_ADTS;
extern const char* AMEDIAFORMAT_KEY_IS_AUTOSELECT;
extern const char* AMEDIAFORMAT_KEY_IS_DEFAULT;
extern const char* AMEDIAFORMAT_KEY_IS_FORCED_SUBTITLE;
extern const char* AMEDIAFORMAT_KEY_I_FRAME_INTERVAL;
extern const char* AMEDIAFORMAT_KEY_LANGUAGE;
extern const char* AMEDIAFORMAT_KEY_LATENCY;
extern const char* AMEDIAFORMAT_KEY_LEVEL;
extern const char* AMEDIAFORMAT_KEY_MAX_HEIGHT;
constexpr static const char* AMEDIAFORMAT_KEY_MAX_INPUT_SIZE = "max-input-size";
extern const char* AMEDIAFORMAT_KEY_MAX_WIDTH;
constexpr static const char* AMEDIAFORMAT_KEY_MIME = "mime";
extern const char* AMEDIAFORMAT_KEY_MPEG_USER_DATA;
extern const char* AMEDIAFORMAT_KEY_OPERATING_RATE;
extern const char* AMEDIAFORMAT_KEY_PCM_ENCODING;
extern const char* AMEDIAFORMAT_KEY_PRIORITY;
extern const char* AMEDIAFORMAT_KEY_PROFILE;
extern const char* AMEDIAFORMAT_KEY_PUSH_BLANK_BUFFERS_ON_STOP;
extern const char* AMEDIAFORMAT_KEY_REPEAT_PREVIOUS_FRAME_AFTER;
extern const char* AMEDIAFORMAT_KEY_ROTATION;
extern const char* AMEDIAFORMAT_KEY_SAMPLE_RATE;
extern const char* AMEDIAFORMAT_KEY_SEI;
constexpr static const char* AMEDIAFORMAT_KEY_SLICE_HEIGHT = "slice-height";
constexpr static const char* AMEDIAFORMAT_KEY_STRIDE = "stride";
extern const char* AMEDIAFORMAT_KEY_TEMPORAL_LAYER_ID;                                                                                                                            
extern const char* AMEDIAFORMAT_KEY_TEMPORAL_LAYERING;
extern const char* AMEDIAFORMAT_KEY_TILE_HEIGHT;
extern const char* AMEDIAFORMAT_KEY_TILE_WIDTH;
extern const char* AMEDIAFORMAT_KEY_TIME_US;
extern const char* AMEDIAFORMAT_KEY_TRACK_ID;
extern const char* AMEDIAFORMAT_KEY_TRACK_INDEX;
constexpr static const char* AMEDIAFORMAT_KEY_WIDTH = "width";
NDKMEDIA_NS_END
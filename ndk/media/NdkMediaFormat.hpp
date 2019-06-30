/*
 * AND: Android Native Dev in Modern C++ based on JMI
 * Copyright (C) 2018-2019 Wang Bin - wbsecg1@gmail.com
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
//#if __ANDROID_API__ >= 28
// api 28 apis are ndk only, no java apis
bool AMediaFormat_getDouble(AMediaFormat*, const char *name, double *out);// __INTRODUCED_IN(28);
bool AMediaFormat_getRect(AMediaFormat*, const char *name, int32_t *left, int32_t *top, int32_t *right, int32_t *bottom);// __INTRODUCED_IN(28);
void AMediaFormat_setDouble(AMediaFormat*, const char* name, double value);// __INTRODUCED_IN(28);
void AMediaFormat_setSize(AMediaFormat*, const char* name, size_t value);// __INTRODUCED_IN(28);
void AMediaFormat_setRect(AMediaFormat*, const char* name, int32_t left, int32_t top, int32_t right, int32_t bottom);// __INTRODUCED_IN(28);
//#endif /* __ANDROID_API__ >= 28 */

// constexpr
constexpr static const char* AMEDIAFORMAT_KEY_AAC_DRC_ATTENUATION_FACTOR = "aac-drc-cut-level"; // 21
constexpr static const char* AMEDIAFORMAT_KEY_AAC_DRC_BOOST_FACTOR = "aac-drc-boost-level"; //21
constexpr static const char* AMEDIAFORMAT_KEY_AAC_DRC_HEAVY_COMPRESSION = "aac-drc-heavy-compression"; // 21
constexpr static const char* AMEDIAFORMAT_KEY_AAC_DRC_TARGET_REFERENCE_LEVEL = "aac-target-ref-level"; // 21
constexpr static const char* AMEDIAFORMAT_KEY_AAC_ENCODED_TARGET_LEVEL = "aac-encoded-target-level"; // 21
constexpr static const char* AMEDIAFORMAT_KEY_AAC_MAX_OUTPUT_CHANNEL_COUNT = "aac-max-output-channel_count"; // 21
constexpr static const char* AMEDIAFORMAT_KEY_AAC_PROFILE = "aac-profile"; // 16
constexpr static const char* AMEDIAFORMAT_KEY_AAC_SBR_MODE = "aac-sbr-mode"; // 21
constexpr static const char* AMEDIAFORMAT_KEY_AUDIO_SESSION_ID = "audio-session-id"; // 21
constexpr static const char* AMEDIAFORMAT_KEY_BITRATE_MODE = "bitrate-mode"; // 21
constexpr static const char* AMEDIAFORMAT_KEY_BIT_RATE = "bitrate"; // 16
constexpr static const char* AMEDIAFORMAT_KEY_CAPTURE_RATE = "capture-rate"; // 21
constexpr static const char* AMEDIAFORMAT_KEY_CHANNEL_COUNT = "channel-count";
constexpr static const char* AMEDIAFORMAT_KEY_CHANNEL_MASK = "channel-mask"; // 16
constexpr static const char* AMEDIAFORMAT_KEY_COLOR_FORMAT = "color-format";
constexpr static const char* AMEDIAFORMAT_KEY_COLOR_RANGE = "color-range"; // 24, int
constexpr static const char* AMEDIAFORMAT_KEY_COLOR_STANDARD = "color-standard"; // 24/28, int
constexpr static const char* AMEDIAFORMAT_KEY_COLOR_TRANSFER = "color-transfer"; // 24/28, int
constexpr static const char* AMEDIAFORMAT_KEY_COMPLEXITY = "complexity"; // 21
constexpr static const char* AMEDIAFORMAT_KEY_CSD = "csd";
constexpr static const char* AMEDIAFORMAT_KEY_CSD_0 = "csd-0";
constexpr static const char* AMEDIAFORMAT_KEY_CSD_1 = "csd-1";
constexpr static const char* AMEDIAFORMAT_KEY_CSD_2 = "csd-2";
extern const char* AMEDIAFORMAT_KEY_DISPLAY_CROP;
extern const char* AMEDIAFORMAT_KEY_DISPLAY_HEIGHT;
extern const char* AMEDIAFORMAT_KEY_DISPLAY_WIDTH;
constexpr static const char* AMEDIAFORMAT_KEY_DURATION = "durationUs"; // 16
constexpr static const char* AMEDIAFORMAT_KEY_FLAC_COMPRESSION_LEVEL = "flac-compression-level"; // 16, int 0~8
constexpr static const char* AMEDIAFORMAT_KEY_FRAME_RATE = "frame-rate"; // 16, int/float
extern const char* AMEDIAFORMAT_KEY_GRID_COLUMNS;
extern const char* AMEDIAFORMAT_KEY_GRID_ROWS;
constexpr static const char* AMEDIAFORMAT_KEY_HDR_STATIC_INFO = "hdr-static-info"; // java24/ndk28. ByteBuffer, CTA-861.3
constexpr static const char* AMEDIAFORMAT_KEY_HEIGHT = "height";
constexpr static const char* AMEDIAFORMAT_KEY_INTRA_REFRESH_PERIOD = "intra-refresh-period"; // 24
constexpr static const char* AMEDIAFORMAT_KEY_IS_ADTS = "is-adts";
constexpr static const char* AMEDIAFORMAT_KEY_IS_AUTOSELECT = "is-autoselect"; // 19
constexpr static const char* AMEDIAFORMAT_KEY_IS_DEFAULT = "is-default";
constexpr static const char* AMEDIAFORMAT_KEY_IS_FORCED_SUBTITLE = "is-forced-subtitle"; // 19
constexpr static const char* AMEDIAFORMAT_KEY_I_FRAME_INTERVAL = "i-frame-interval"; // 16
constexpr static const char* AMEDIAFORMAT_KEY_LANGUAGE = "language"; // 19
constexpr static const char* AMEDIAFORMAT_KEY_LATENCY = "latency"; // 26
constexpr static const char* AMEDIAFORMAT_KEY_LEVEL = "level"; // 23, enc
constexpr static const char* AMEDIAFORMAT_KEY_MAX_HEIGHT = "max-height"; // 19
constexpr static const char* AMEDIAFORMAT_KEY_MAX_INPUT_SIZE = "max-input-size";
constexpr static const char* AMEDIAFORMAT_KEY_MAX_WIDTH = "max-width"; // 19
constexpr static const char* AMEDIAFORMAT_KEY_MIME = "mime";
extern const char* AMEDIAFORMAT_KEY_MPEG_USER_DATA;
constexpr static const char* AMEDIAFORMAT_KEY_OPERATING_RATE = "operating-rate";
constexpr static const char* AMEDIAFORMAT_KEY_PCM_ENCODING = "pcm-encoding";
extern const char* AMEDIAFORMAT_KEY_PRIORITY; // 23
constexpr static const char* AMEDIAFORMAT_KEY_PROFILE = "profile"; // 21
constexpr static const char* AMEDIAFORMAT_KEY_PUSH_BLANK_BUFFERS_ON_STOP = "push-blank-buffers-on-shutdown"; // 19
constexpr static const char* AMEDIAFORMAT_KEY_REPEAT_PREVIOUS_FRAME_AFTER = "repeat-previous-frame-after"; // 19
constexpr static const char* AMEDIAFORMAT_KEY_ROTATION = "rotation-degrees"; // 23
constexpr static const char* AMEDIAFORMAT_KEY_SAMPLE_RATE = "sample-rate";
extern const char* AMEDIAFORMAT_KEY_SEI;
constexpr static const char* AMEDIAFORMAT_KEY_SLICE_HEIGHT = "slice-height";
constexpr static const char* AMEDIAFORMAT_KEY_STRIDE = "stride";
extern const char* AMEDIAFORMAT_KEY_TEMPORAL_LAYER_ID;                                                                                                                            
constexpr static const char* AMEDIAFORMAT_KEY_TEMPORAL_LAYERING = "ts-schema"; // 21
extern const char* AMEDIAFORMAT_KEY_TILE_HEIGHT;
extern const char* AMEDIAFORMAT_KEY_TILE_WIDTH;
extern const char* AMEDIAFORMAT_KEY_TIME_US;
constexpr static const char* AMEDIAFORMAT_KEY_TRACK_ID = "track-id"; // 24
extern const char* AMEDIAFORMAT_KEY_TRACK_INDEX;
constexpr static const char* AMEDIAFORMAT_KEY_WIDTH = "width";
NDKMEDIA_NS_END
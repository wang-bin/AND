
/*
 * AND: Android Native Dev in Modern C++ based on JMI
 * Copyright (C) 2018-2019 Wang Bin - wbsecg1@gmail.com
 * https://github.com/wang-bin/AND
 * https://github.com/wang-bin/JMI
 * MIT License
 */
// if introduced in ndk api > 21 or java api > 16, MUST check return value, which is AMEDIA_ERROR_UNSUPPORTED if not supported by ndk

#pragma once
#include "NdkMediaCrypto.hpp"
#include "NdkMediaFormat.hpp"
#include <android/native_window.h>
#include <sys/cdefs.h>
#include <sys/types.h>

NDKMEDIA_NS_BEGIN

struct AMediaCodec;
typedef struct AMediaCodec AMediaCodec;

struct AMediaCodecBufferInfo {
    int32_t offset;
    int32_t size;
    int64_t presentationTimeUs;
    uint32_t flags;
};
typedef struct AMediaCodecBufferInfo AMediaCodecBufferInfo;
typedef struct AMediaCodecCryptoInfo AMediaCodecCryptoInfo;

enum {                
    //AMEDIACODEC_BUFFER_FLAG_KEY_FRAME = 1,
    AMEDIACODEC_BUFFER_FLAG_CODEC_CONFIG = 2,
    AMEDIACODEC_BUFFER_FLAG_END_OF_STREAM = 4,
    AMEDIACODEC_BUFFER_FLAG_PARTIAL_FRAME = 8,

    AMEDIACODEC_CONFIGURE_FLAG_ENCODE = 1,
    AMEDIACODEC_INFO_OUTPUT_BUFFERS_CHANGED = -3,
    AMEDIACODEC_INFO_OUTPUT_FORMAT_CHANGED = -2,
    AMEDIACODEC_INFO_TRY_AGAIN_LATER = -1,
};

AMediaCodec* AMediaCodec_createCodecByName(const char *name);
AMediaCodec* AMediaCodec_createDecoderByType(const char *mime_type);
AMediaCodec* AMediaCodec_createEncoderByType(const char *mime_type);
media_status_t AMediaCodec_delete(AMediaCodec*);
// surface: jni accepts Surface jobject instead of ANativeWindow*
media_status_t AMediaCodec_configure(AMediaCodec*, const AMediaFormat* format, ANativeWindow* surface, AMediaCrypto *crypto, uint32_t flags);
media_status_t AMediaCodec_start(AMediaCodec*);
media_status_t AMediaCodec_stop(AMediaCodec*);
media_status_t AMediaCodec_flush(AMediaCodec*);
uint8_t* AMediaCodec_getInputBuffer(AMediaCodec*, size_t idx, size_t *out_size);
uint8_t* AMediaCodec_getOutputBuffer(AMediaCodec*, size_t idx, size_t *out_size);
ssize_t AMediaCodec_dequeueInputBuffer(AMediaCodec*, int64_t timeoutUs);

// c11/c++11: _off_t_compat == long
media_status_t AMediaCodec_queueInputBuffer(AMediaCodec*, size_t idx, long offset, size_t size, uint64_t time, uint32_t flags);
media_status_t AMediaCodec_queueSecureInputBuffer(AMediaCodec*, size_t idx, long offset, AMediaCodecCryptoInfo*, uint64_t time, uint32_t flags);

ssize_t AMediaCodec_dequeueOutputBuffer(AMediaCodec*, AMediaCodecBufferInfo *info, int64_t timeoutUs); // __INTRODUCED_IN(21), java 16
AMediaFormat* AMediaCodec_getOutputFormat(AMediaCodec*); // __INTRODUCED_IN(21), java 16 // owned by AMediaCodec
media_status_t AMediaCodec_releaseOutputBuffer(AMediaCodec*, size_t idx, bool render); // __INTRODUCED_IN(21), java 16
media_status_t AMediaCodec_setOutputSurface(AMediaCodec*, ANativeWindow* surface); // __INTRODUCED_IN(21), java 23
media_status_t AMediaCodec_releaseOutputBufferAtTime(AMediaCodec*, size_t idx, int64_t timestampNs); // __INTRODUCED_IN(21), java 21

// encoders
media_status_t AMediaCodec_createInputSurface(AMediaCodec*, ANativeWindow **surface); // __INTRODUCED_IN(26), java 18
media_status_t AMediaCodec_createPersistentInputSurface(ANativeWindow **surface); // __INTRODUCED_IN(26), java 23
media_status_t AMediaCodec_setInputSurface(AMediaCodec*, ANativeWindow *surface); // __INTRODUCED_IN(26), java 23
media_status_t AMediaCodec_setParameters(AMediaCodec*, const AMediaFormat* params); // __INTRODUCED_IN(26), java 19
media_status_t AMediaCodec_signalEndOfInputStream(AMediaCodec*); // __INTRODUCED_IN(26), java 18

// TODO: AMediaCodecCryptoInfo_new... (21)

// 28
media_status_t AMediaCodec_getName(AMediaCodec*, char** out_name);// __INTRODUCED_IN(28), java 18
void AMediaCodec_releaseName(AMediaCodec*, char* name);// __INTRODUCED_IN(28). no java
//media_status_t AMediaCodec_setAsyncNotifyCallback(AMediaCodec*, AMediaCodecOnAsyncNotifyCallback callback, void *userdata);
NDKMEDIA_NS_END

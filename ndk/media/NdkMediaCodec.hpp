
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

/**
 * Called when an input buffer becomes available.
 * The specified index is the index of the available input buffer.
 */
typedef void (*AMediaCodecOnAsyncInputAvailable)(AMediaCodec *codec, void *userdata, int32_t index);
/**
 * Called when an output buffer becomes available.
 * The specified index is the index of the available output buffer.
 * The specified bufferInfo contains information regarding the available output buffer.
 */
typedef void (*AMediaCodecOnAsyncOutputAvailable)(AMediaCodec *codec, void *userdata, int32_t index, AMediaCodecBufferInfo *bufferInfo);
/**
 * Called when the output format has changed.
 * The specified format contains the new output format.
 */
typedef void (*AMediaCodecOnAsyncFormatChanged)(AMediaCodec *codec, void *userdata, AMediaFormat *format);
/**
 * Called when the MediaCodec encountered an error.
 * The specified actionCode indicates the possible actions that client can take,
 * and it can be checked by calling AMediaCodecActionCode_isRecoverable or
 * AMediaCodecActionCode_isTransient. If both AMediaCodecActionCode_isRecoverable()
 * and AMediaCodecActionCode_isTransient() return false, then the codec error is fatal
 * and the codec must be deleted.
 * The specified detail may contain more detailed messages about this error.
 */
typedef void (*AMediaCodecOnAsyncError)(AMediaCodec *codec, void *userdata, media_status_t error, int32_t actionCode, const char *detail);

struct AMediaCodecOnAsyncNotifyCallback {
      AMediaCodecOnAsyncInputAvailable  onAsyncInputAvailable;
      AMediaCodecOnAsyncOutputAvailable onAsyncOutputAvailable;
      AMediaCodecOnAsyncFormatChanged   onAsyncFormatChanged;
      AMediaCodecOnAsyncError           onAsyncError;
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

ssize_t AMediaCodec_dequeueOutputBuffer(AMediaCodec*, AMediaCodecBufferInfo *info, int64_t timeoutUs); // java 16
AMediaFormat* AMediaCodec_getOutputFormat(AMediaCodec*); // java 16. AMediaFormat_delete by user
media_status_t AMediaCodec_releaseOutputBuffer(AMediaCodec*, size_t idx, bool render); // java 16
media_status_t AMediaCodec_setOutputSurface(AMediaCodec*, ANativeWindow* surface); // java 23
media_status_t AMediaCodec_releaseOutputBufferAtTime(AMediaCodec*, size_t idx, int64_t timestampNs); // java 21

// encoders
media_status_t AMediaCodec_createInputSurface(AMediaCodec*, ANativeWindow **surface); // __INTRODUCED_IN(26), java 18
media_status_t AMediaCodec_createPersistentInputSurface(ANativeWindow **surface); // __INTRODUCED_IN(26), java 23
media_status_t AMediaCodec_setInputSurface(AMediaCodec*, ANativeWindow *surface); // __INTRODUCED_IN(26), java 23
media_status_t AMediaCodec_setParameters(AMediaCodec*, const AMediaFormat* params); // __INTRODUCED_IN(26), java 19
// Equivalent to submitting an empty buffer with BUFFER_FLAG_END_OF_STREAM set. This may only be used with encoders receiving input from a Surface created by createInputSurface()
media_status_t AMediaCodec_signalEndOfInputStream(AMediaCodec*); // __INTRODUCED_IN(26), java 18. Signals end-of-stream on input.

// TODO: AMediaCodecCryptoInfo_new... (21)

// 28
/**
 * Get format of the buffer. The specified buffer index must have been previously obtained from
 * dequeueOutputBuffer.
 */
AMediaFormat* AMediaCodec_getBufferFormat(AMediaCodec*, size_t index);// __INTRODUCED_IN(28);. java 21 getOutputFormat(int). AMediaFormat_delete by user

media_status_t AMediaCodec_getName(AMediaCodec*, char** out_name);// __INTRODUCED_IN(28), java 18
void AMediaCodec_releaseName(AMediaCodec*, char* name);// __INTRODUCED_IN(28). no java

/**
 * Set an asynchronous callback for actionable AMediaCodec events.
 * When asynchronous callback is enabled, the client should not call
 * AMediaCodec_getInputBuffers(), AMediaCodec_getOutputBuffers(),
 * AMediaCodec_dequeueInputBuffer() or AMediaCodec_dequeueOutputBuffer().
 *
 * Also, AMediaCodec_flush() behaves differently in asynchronous mode.
 * After calling AMediaCodec_flush(), you must call AMediaCodec_start() to
 * "resume" receiving input buffers, even if an input surface was created.
 *
 * All callbacks are fired on one NDK internal thread.
 * AMediaCodec_setAsyncNotifyCallback should not be called on the callback thread.
 * No heavy duty task should be performed on callback thread.
 */
media_status_t AMediaCodec_setAsyncNotifyCallback(AMediaCodec*, AMediaCodecOnAsyncNotifyCallback callback, void *userdata);// __INTRODUCED_IN(28);

//media_status_t AMediaCodec_releaseCrypto(AMediaCodec*);// __INTRODUCED_IN(28);

/**
 * Call this after AMediaCodec_configure() returns successfully to get the input
 * format accepted by the codec. Do this to determine what optional configuration
 * parameters were supported by the codec.
 */
AMediaFormat* AMediaCodec_getInputFormat(AMediaCodec*);// __INTRODUCED_IN(28); java 21. AMediaFormat_delete by user

/**
 * Returns true if the codec cannot proceed further, but can be recovered by stopping,
 * configuring, and starting again.
 */
bool AMediaCodecActionCode_isRecoverable(int32_t actionCode);// __INTRODUCED_IN(28);

/**
 * Returns true if the codec error is a transient issue, perhaps due to
 * resource constraints, and that the method (or encoding/decoding) may be
 * retried at a later time.
 */
bool AMediaCodecActionCode_isTransient(int32_t actionCode);// __INTRODUCED_IN(28);
NDKMEDIA_NS_END

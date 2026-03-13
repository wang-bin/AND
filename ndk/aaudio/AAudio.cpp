/*
 * AND: Android Native Dev in Modern C++ based on JMI
 * Copyright (C) 2026 Wang Bin - wbsecg1@gmail.com
 * https://github.com/wang-bin/AND
 * https://github.com/wang-bin/JMI
 * MIT License
 */

#include <aaudio/AAudio.h>
#include <dlfcn.h>
#define NDKCOMPAT_API_DECL AAUDIO_API
#include "../NdkCompatAPI.h"

namespace {

void* aaudio_so()
{
	static void* so = dlopen("libaaudio.so", RTLD_NOW | RTLD_LOCAL);
	return so;
}

void* resolve(const char* name)
{
	if (auto so = aaudio_so())
		return dlsym(so, name);
	return nullptr;
}

} // namespace

// weak: avoid duplicated symbol if current object is depended by multiple modules and appears multiple times in the link
NDKCOMPAT_DEFINE_RET(const char*, AAudio_convertResultToText, "AAUDIO_ERROR_UNIMPLEMENTED", JMI_ARG1(aaudio_result_t))
NDKCOMPAT_DEFINE_RET(const char*, AAudio_convertStreamStateToText, "AAUDIO_STREAM_STATE_UNKNOWN", JMI_ARG1(aaudio_stream_state_t))
NDKCOMPAT_DEFINE_RET(aaudio_result_t, AAudio_createStreamBuilder, AAUDIO_ERROR_UNIMPLEMENTED, JMI_ARG1(AAudioStreamBuilder**))

NDKCOMPAT_DEFINE_VOID(AAudioStreamBuilder_setDeviceId, JMI_ARG2(AAudioStreamBuilder*, int32_t))
NDKCOMPAT_DEFINE_VOID(AAudioStreamBuilder_setPackageName, JMI_ARG2(AAudioStreamBuilder*, const char*))
NDKCOMPAT_DEFINE_VOID(AAudioStreamBuilder_setAttributionTag, JMI_ARG2(AAudioStreamBuilder*, const char*))
NDKCOMPAT_DEFINE_VOID(AAudioStreamBuilder_setSampleRate, JMI_ARG2(AAudioStreamBuilder*, int32_t))
NDKCOMPAT_DEFINE_VOID(AAudioStreamBuilder_setChannelCount, JMI_ARG2(AAudioStreamBuilder*, int32_t))
NDKCOMPAT_DEFINE_VOID(AAudioStreamBuilder_setSamplesPerFrame, JMI_ARG2(AAudioStreamBuilder*, int32_t))
NDKCOMPAT_DEFINE_VOID(AAudioStreamBuilder_setFormat, JMI_ARG2(AAudioStreamBuilder*, aaudio_format_t))
NDKCOMPAT_DEFINE_VOID(AAudioStreamBuilder_setSharingMode, JMI_ARG2(AAudioStreamBuilder*, aaudio_sharing_mode_t))
NDKCOMPAT_DEFINE_VOID(AAudioStreamBuilder_setDirection, JMI_ARG2(AAudioStreamBuilder*, aaudio_direction_t))
NDKCOMPAT_DEFINE_VOID(AAudioStreamBuilder_setBufferCapacityInFrames, JMI_ARG2(AAudioStreamBuilder*, int32_t))
NDKCOMPAT_DEFINE_VOID(AAudioStreamBuilder_setPerformanceMode, JMI_ARG2(AAudioStreamBuilder*, aaudio_performance_mode_t))
NDKCOMPAT_DEFINE_VOID(AAudioStreamBuilder_setUsage, JMI_ARG2(AAudioStreamBuilder*, aaudio_usage_t))
NDKCOMPAT_DEFINE_VOID(AAudioStreamBuilder_setContentType, JMI_ARG2(AAudioStreamBuilder*, aaudio_content_type_t))
NDKCOMPAT_DEFINE_VOID(AAudioStreamBuilder_setSpatializationBehavior, JMI_ARG2(AAudioStreamBuilder*, aaudio_spatialization_behavior_t))
NDKCOMPAT_DEFINE_VOID(AAudioStreamBuilder_setIsContentSpatialized, JMI_ARG2(AAudioStreamBuilder*, bool))
NDKCOMPAT_DEFINE_VOID(AAudioStreamBuilder_setInputPreset, JMI_ARG2(AAudioStreamBuilder*, aaudio_input_preset_t))
NDKCOMPAT_DEFINE_VOID(AAudioStreamBuilder_setAllowedCapturePolicy, JMI_ARG2(AAudioStreamBuilder*, aaudio_allowed_capture_policy_t))
NDKCOMPAT_DEFINE_VOID(AAudioStreamBuilder_setSessionId, JMI_ARG2(AAudioStreamBuilder*, aaudio_session_id_t))
NDKCOMPAT_DEFINE_VOID(AAudioStreamBuilder_setPrivacySensitive, JMI_ARG2(AAudioStreamBuilder*, bool))
NDKCOMPAT_DEFINE_VOID(AAudioStreamBuilder_setDataCallback, JMI_ARG3(AAudioStreamBuilder*, AAudioStream_dataCallback, void*))
NDKCOMPAT_DEFINE_VOID(AAudioStreamBuilder_setFramesPerDataCallback, JMI_ARG2(AAudioStreamBuilder*, int32_t))
NDKCOMPAT_DEFINE_VOID(AAudioStreamBuilder_setErrorCallback, JMI_ARG3(AAudioStreamBuilder*, AAudioStream_errorCallback, void*))

NDKCOMPAT_DEFINE_RET(aaudio_result_t, AAudioStreamBuilder_openStream, AAUDIO_ERROR_UNIMPLEMENTED, JMI_ARG2(AAudioStreamBuilder*, AAudioStream**))
NDKCOMPAT_DEFINE_RET(aaudio_result_t, AAudioStreamBuilder_delete, AAUDIO_ERROR_UNIMPLEMENTED, JMI_ARG1(AAudioStreamBuilder*))
NDKCOMPAT_DEFINE_VOID(AAudioStreamBuilder_setChannelMask, JMI_ARG2(AAudioStreamBuilder*, aaudio_channel_mask_t))

NDKCOMPAT_DEFINE_RET(aaudio_result_t, AAudioStream_release, AAUDIO_ERROR_UNIMPLEMENTED, JMI_ARG1(AAudioStream*))
NDKCOMPAT_DEFINE_RET(aaudio_result_t, AAudioStream_close, AAUDIO_ERROR_UNIMPLEMENTED, JMI_ARG1(AAudioStream*))
NDKCOMPAT_DEFINE_RET(aaudio_result_t, AAudioStream_requestStart, AAUDIO_ERROR_UNIMPLEMENTED, JMI_ARG1(AAudioStream*))
NDKCOMPAT_DEFINE_RET(aaudio_result_t, AAudioStream_requestPause, AAUDIO_ERROR_UNIMPLEMENTED, JMI_ARG1(AAudioStream*))
NDKCOMPAT_DEFINE_RET(aaudio_result_t, AAudioStream_requestFlush, AAUDIO_ERROR_UNIMPLEMENTED, JMI_ARG1(AAudioStream*))
NDKCOMPAT_DEFINE_RET(aaudio_result_t, AAudioStream_requestStop, AAUDIO_ERROR_UNIMPLEMENTED, JMI_ARG1(AAudioStream*))
NDKCOMPAT_DEFINE_RET(aaudio_stream_state_t, AAudioStream_getState, AAUDIO_STREAM_STATE_UNKNOWN, JMI_ARG1(AAudioStream*))

NDKCOMPAT_DEFINE_RET(aaudio_result_t, AAudioStream_waitForStateChange, AAUDIO_ERROR_UNIMPLEMENTED, JMI_ARG4(AAudioStream*, aaudio_stream_state_t, aaudio_stream_state_t*, int64_t))
NDKCOMPAT_DEFINE_RET(aaudio_result_t, AAudioStream_read, AAUDIO_ERROR_UNIMPLEMENTED, JMI_ARG4(AAudioStream*, void*, int32_t, int64_t))
NDKCOMPAT_DEFINE_RET(aaudio_result_t, AAudioStream_write, AAUDIO_ERROR_UNIMPLEMENTED, JMI_ARG4(AAudioStream*, const void*, int32_t, int64_t))
NDKCOMPAT_DEFINE_RET(aaudio_result_t, AAudioStream_setBufferSizeInFrames, AAUDIO_ERROR_UNIMPLEMENTED, JMI_ARG2(AAudioStream*, int32_t))

NDKCOMPAT_DEFINE_RET(int32_t, AAudioStream_getBufferSizeInFrames, 0, JMI_ARG1(AAudioStream*))
NDKCOMPAT_DEFINE_RET(int32_t, AAudioStream_getFramesPerBurst, 0, JMI_ARG1(AAudioStream*))
NDKCOMPAT_DEFINE_RET(int32_t, AAudioStream_getBufferCapacityInFrames, 0, JMI_ARG1(AAudioStream*))
NDKCOMPAT_DEFINE_RET(int32_t, AAudioStream_getFramesPerDataCallback, AAUDIO_UNSPECIFIED, JMI_ARG1(AAudioStream*))
NDKCOMPAT_DEFINE_RET(int32_t, AAudioStream_getXRunCount, 0, JMI_ARG1(AAudioStream*))
NDKCOMPAT_DEFINE_RET(int32_t, AAudioStream_getSampleRate, AAUDIO_UNSPECIFIED, JMI_ARG1(AAudioStream*))
NDKCOMPAT_DEFINE_RET(int32_t, AAudioStream_getHardwareSampleRate, AAUDIO_UNSPECIFIED, JMI_ARG1(AAudioStream*))
NDKCOMPAT_DEFINE_RET(int32_t, AAudioStream_getChannelCount, AAUDIO_UNSPECIFIED, JMI_ARG1(AAudioStream*))
NDKCOMPAT_DEFINE_RET(int32_t, AAudioStream_getHardwareChannelCount, AAUDIO_UNSPECIFIED, JMI_ARG1(AAudioStream*))
NDKCOMPAT_DEFINE_RET(int32_t, AAudioStream_getSamplesPerFrame, AAUDIO_UNSPECIFIED, JMI_ARG1(AAudioStream*))
NDKCOMPAT_DEFINE_RET(int32_t, AAudioStream_getDeviceId, AAUDIO_UNSPECIFIED, JMI_ARG1(AAudioStream*))
NDKCOMPAT_DEFINE_RET(aaudio_format_t, AAudioStream_getFormat, AAUDIO_FORMAT_INVALID, JMI_ARG1(AAudioStream*))
NDKCOMPAT_DEFINE_RET(aaudio_format_t, AAudioStream_getHardwareFormat, AAUDIO_FORMAT_INVALID, JMI_ARG1(AAudioStream*))
NDKCOMPAT_DEFINE_RET(aaudio_sharing_mode_t, AAudioStream_getSharingMode, AAUDIO_SHARING_MODE_SHARED, JMI_ARG1(AAudioStream*))
NDKCOMPAT_DEFINE_RET(aaudio_performance_mode_t, AAudioStream_getPerformanceMode, AAUDIO_PERFORMANCE_MODE_NONE, JMI_ARG1(AAudioStream*))
NDKCOMPAT_DEFINE_RET(aaudio_direction_t, AAudioStream_getDirection, AAUDIO_DIRECTION_OUTPUT, JMI_ARG1(AAudioStream*))
NDKCOMPAT_DEFINE_RET(int64_t, AAudioStream_getFramesWritten, 0, JMI_ARG1(AAudioStream*))
NDKCOMPAT_DEFINE_RET(int64_t, AAudioStream_getFramesRead, 0, JMI_ARG1(AAudioStream*))
NDKCOMPAT_DEFINE_RET(aaudio_session_id_t, AAudioStream_getSessionId, AAUDIO_SESSION_ID_NONE, JMI_ARG1(AAudioStream*))

NDKCOMPAT_DEFINE_RET(aaudio_result_t, AAudioStream_getTimestamp, AAUDIO_ERROR_UNIMPLEMENTED, JMI_ARG4(AAudioStream*, clockid_t, int64_t*, int64_t*))
NDKCOMPAT_DEFINE_RET(aaudio_usage_t, AAudioStream_getUsage, AAUDIO_USAGE_MEDIA, JMI_ARG1(AAudioStream*))
NDKCOMPAT_DEFINE_RET(aaudio_content_type_t, AAudioStream_getContentType, AAUDIO_CONTENT_TYPE_MUSIC, JMI_ARG1(AAudioStream*))
NDKCOMPAT_DEFINE_RET(aaudio_spatialization_behavior_t, AAudioStream_getSpatializationBehavior, AAUDIO_SPATIALIZATION_BEHAVIOR_AUTO, JMI_ARG1(AAudioStream*))
NDKCOMPAT_DEFINE_RET(bool, AAudioStream_isContentSpatialized, false, JMI_ARG1(AAudioStream*))
NDKCOMPAT_DEFINE_RET(aaudio_input_preset_t, AAudioStream_getInputPreset, AAUDIO_INPUT_PRESET_GENERIC, JMI_ARG1(AAudioStream*))
NDKCOMPAT_DEFINE_RET(aaudio_allowed_capture_policy_t, AAudioStream_getAllowedCapturePolicy, AAUDIO_ALLOW_CAPTURE_BY_ALL, JMI_ARG1(AAudioStream*))
NDKCOMPAT_DEFINE_RET(bool, AAudioStream_isPrivacySensitive, false, JMI_ARG1(AAudioStream*))
NDKCOMPAT_DEFINE_RET(aaudio_channel_mask_t, AAudioStream_getChannelMask, static_cast<aaudio_channel_mask_t>(AAUDIO_UNSPECIFIED), JMI_ARG1(AAudioStream*))

#if (__NDK_MAJOR__ + 0) >= 29 // defines api 36
NDKCOMPAT_DEFINE_VOID(AAudioStreamBuilder_setPresentationEndCallback, JMI_ARG3(AAudioStreamBuilder*, AAudioStream_presentationEndCallback, void*)) // api 36+, requires ndk 29
NDKCOMPAT_DEFINE_RET(aaudio_result_t, AAudioStream_setOffloadDelayPadding, AAUDIO_ERROR_UNIMPLEMENTED, JMI_ARG3(AAudioStream*, int32_t, int32_t))
NDKCOMPAT_DEFINE_RET(int32_t, AAudioStream_getOffloadDelay, AAUDIO_ERROR_UNIMPLEMENTED, JMI_ARG1(AAudioStream*))
NDKCOMPAT_DEFINE_RET(int32_t, AAudioStream_getOffloadPadding, AAUDIO_ERROR_UNIMPLEMENTED, JMI_ARG1(AAudioStream*))
NDKCOMPAT_DEFINE_RET(aaudio_result_t, AAudioStream_setOffloadEndOfStream, AAUDIO_ERROR_UNIMPLEMENTED, JMI_ARG1(AAudioStream*))
#endif //__ANDROID_API_V__
#undef NDKCOMPAT_API_DECL

/*
 * AND: Android Native Dev in Modern C++ based on JMI
 * Copyright (C) 2026 Wang Bin - wbsecg1@gmail.com
 * https://github.com/wang-bin/AND
 * https://github.com/wang-bin/JMI
 * MIT License
 */
#if (__ANDROID_API__ + 0) < 21
#include <media/NdkImage.h>
#include <dlfcn.h>
#include "NdkMedia.h"
#include "../NdkCompatAPI.h"

namespace {

void* resolve(const char* name)
{
	if (auto so = NDKMEDIA_NS::mediandk_so())
		return dlsym(so, name);
	return nullptr;
}

} // namespace

NDKCOMPAT_DEFINE_VOID(AImage_delete, JMI_ARG1(AImage*))
NDKCOMPAT_DEFINE_RET(media_status_t, AImage_getWidth, AMEDIA_ERROR_UNSUPPORTED, JMI_ARG2(const AImage*, int32_t*))
NDKCOMPAT_DEFINE_RET(media_status_t, AImage_getHeight, AMEDIA_ERROR_UNSUPPORTED, JMI_ARG2(const AImage*, int32_t*))
NDKCOMPAT_DEFINE_RET(media_status_t, AImage_getFormat, AMEDIA_ERROR_UNSUPPORTED, JMI_ARG2(const AImage*, int32_t*))
NDKCOMPAT_DEFINE_RET(media_status_t, AImage_getCropRect, AMEDIA_ERROR_UNSUPPORTED, JMI_ARG2(const AImage*, AImageCropRect*))
NDKCOMPAT_DEFINE_RET(media_status_t, AImage_getTimestamp, AMEDIA_ERROR_UNSUPPORTED, JMI_ARG2(const AImage*, int64_t*))
NDKCOMPAT_DEFINE_RET(media_status_t, AImage_getNumberOfPlanes, AMEDIA_ERROR_UNSUPPORTED, JMI_ARG2(const AImage*, int32_t*))
NDKCOMPAT_DEFINE_RET(media_status_t, AImage_getPlanePixelStride, AMEDIA_ERROR_UNSUPPORTED, JMI_ARG3(const AImage*, int, int32_t*))
NDKCOMPAT_DEFINE_RET(media_status_t, AImage_getPlaneRowStride, AMEDIA_ERROR_UNSUPPORTED, JMI_ARG3(const AImage*, int, int32_t*))
NDKCOMPAT_DEFINE_RET(media_status_t, AImage_getPlaneData, AMEDIA_ERROR_UNSUPPORTED, JMI_ARG4(const AImage*, int, uint8_t**, int*))
NDKCOMPAT_DEFINE_VOID(AImage_deleteAsync, JMI_ARG2(AImage*, int))
NDKCOMPAT_DEFINE_RET(media_status_t, AImage_getHardwareBuffer, AMEDIA_ERROR_UNSUPPORTED, JMI_ARG2(const AImage*, AHardwareBuffer**))
NDKCOMPAT_DEFINE_RET(media_status_t, AImage_getDataSpace, AMEDIA_ERROR_UNSUPPORTED, JMI_ARG2(const AImage*, int32_t*))

#endif // (__ANDROID_API__ + 0) < 21

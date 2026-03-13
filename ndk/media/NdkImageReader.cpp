/*
 * AND: Android Native Dev in Modern C++ based on JMI
 * Copyright (C) 2026 Wang Bin - wbsecg1@gmail.com
 * https://github.com/wang-bin/AND
 * https://github.com/wang-bin/JMI
 * MIT License
 */

#include <media/NdkImageReader.h>
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

NDKCOMPAT_DEFINE_RET(media_status_t, AImageReader_new, AMEDIA_ERROR_UNSUPPORTED, JMI_ARG5(int32_t, int32_t, int32_t, int32_t, AImageReader**))
NDKCOMPAT_DEFINE_VOID(AImageReader_delete, JMI_ARG1(AImageReader*))
NDKCOMPAT_DEFINE_RET(media_status_t, AImageReader_getWindow, AMEDIA_ERROR_UNSUPPORTED, JMI_ARG2(AImageReader*, ANativeWindow**))
NDKCOMPAT_DEFINE_RET(media_status_t, AImageReader_getWidth, AMEDIA_ERROR_UNSUPPORTED, JMI_ARG2(const AImageReader*, int32_t*))
NDKCOMPAT_DEFINE_RET(media_status_t, AImageReader_getHeight, AMEDIA_ERROR_UNSUPPORTED, JMI_ARG2(const AImageReader*, int32_t*))
NDKCOMPAT_DEFINE_RET(media_status_t, AImageReader_getFormat, AMEDIA_ERROR_UNSUPPORTED, JMI_ARG2(const AImageReader*, int32_t*))
NDKCOMPAT_DEFINE_RET(media_status_t, AImageReader_getMaxImages, AMEDIA_ERROR_UNSUPPORTED, JMI_ARG2(const AImageReader*, int32_t*))
NDKCOMPAT_DEFINE_RET(media_status_t, AImageReader_acquireNextImage, AMEDIA_ERROR_UNSUPPORTED, JMI_ARG2(AImageReader*, AImage**))
NDKCOMPAT_DEFINE_RET(media_status_t, AImageReader_acquireLatestImage, AMEDIA_ERROR_UNSUPPORTED, JMI_ARG2(AImageReader*, AImage**))
NDKCOMPAT_DEFINE_RET(media_status_t, AImageReader_setImageListener, AMEDIA_ERROR_UNSUPPORTED, JMI_ARG2(AImageReader*, AImageReader_ImageListener*))
NDKCOMPAT_DEFINE_RET(media_status_t, AImageReader_newWithUsage, AMEDIA_ERROR_UNSUPPORTED, JMI_ARG6(int32_t, int32_t, int32_t, uint64_t, int32_t, AImageReader**))
NDKCOMPAT_DEFINE_RET(media_status_t, AImageReader_newWithDataSpace, AMEDIA_ERROR_UNSUPPORTED, JMI_ARG7(int32_t, int32_t, uint64_t, int32_t, uint32_t, int32_t, AImageReader**))

NDKCOMPAT_DEFINE_RET(media_status_t, AImageReader_acquireNextImageAsync, AMEDIA_ERROR_UNSUPPORTED, JMI_ARG3(AImageReader*, AImage**, int*))
NDKCOMPAT_DEFINE_RET(media_status_t, AImageReader_acquireLatestImageAsync, AMEDIA_ERROR_UNSUPPORTED, JMI_ARG3(AImageReader*, AImage**, int*))
NDKCOMPAT_DEFINE_RET(media_status_t, AImageReader_setBufferRemovedListener, AMEDIA_ERROR_UNSUPPORTED, JMI_ARG2(AImageReader*, AImageReader_BufferRemovedListener*))

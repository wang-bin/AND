/*
 * AND: Android Native Dev in Modern C++ based on JMI
 * Copyright (C) 2018-2019 Wang Bin - wbsecg1@gmail.com
 * https://github.com/wang-bin/AND
 * https://github.com/wang-bin/JMI
 * MIT License
 */

#include "NdkMediaCrypto.hpp"
#include "android.media.MediaCrypto.hpp"
#include <dlfcn.h>
#include <iostream>
NDKMEDIA_NS_BEGIN
using namespace jmi;
extern void* mediandk_so();

struct AMediaCrypto {
    AMediaCrypto* ndk_; // what ptr type does not matter, but AMediaCrypto* can simplify implementation
    android::media::MediaCrypto jni_; //
};

AMediaCrypto* fromJmi(android::media::MediaCrypto&& jfmt)
{
    return new AMediaCrypto{nullptr, std::move(jfmt)};
}

android::media::MediaCrypto toJmi(const AMediaCrypto* obj)
{
    if (!obj)
        return android::media::MediaCrypto();
    return obj->jni_;
}

AMediaCrypto* fromNdk(AMediaCrypto* obj)
{
    if (!obj)
        return nullptr;
    return new AMediaCrypto{obj};
}

AMediaCrypto* toNdk(const AMediaCrypto* obj)
{
    if (!obj)
        return nullptr;
    return obj->ndk_;
}

AMediaCrypto* AMediaCrypto_new(const AMediaUUID uuid, const void *initData, size_t initDataSize)
{
    void* so = mediandk_so();
    if (!so) {
        android::media::MediaCrypto obj;
        // TODO:
        //if (!obj.create())
         //   return nullptr;
        return new AMediaCrypto{nullptr, std::move(obj)};
    }
    static auto fp = (decltype(&AMediaCrypto_new))dlsym(so, __func__);
    return fromNdk(fp(uuid, initData, initDataSize));
}

void AMediaCrypto_delete(AMediaCrypto* obj)
{
    if (!obj) // required if used as smart ptr deleter
        return;
    void* so = mediandk_so();
    if (so) {
        static auto fp = (decltype(&AMediaCrypto_delete))dlsym(so, __func__);
        fp(obj->ndk_);
        delete obj;
        return;
    }
    if (obj->jni_) {
        obj->jni_.release();
        if (!obj->jni_.error().empty())
            std::clog << __PRETTY_FUNCTION__ << " ERROR: " << obj->jni_.error() << std::endl;
    }
    delete obj;
}

bool AMediaCrypto_isCryptoSchemeSupported(const AMediaUUID uuid)
{
    return false; // TODO:
}

bool AMediaCrypto_requiresSecureDecoderComponent(const char *mime)
{
    void* so = mediandk_so();
    if (!so) {
        return false; // TODO: not static?
    }
    static auto fp = (decltype(&AMediaCrypto_requiresSecureDecoderComponent))dlsym(so, __func__);
    return fp(mime);
}
NDKMEDIA_NS_END
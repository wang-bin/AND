/*
 * AND: Android Native Dev in Modern C++ based on JMI
 * Copyright (C) 2018 Wang Bin - wbsecg1@gmail.com
 * https://github.com/wang-bin/AND
 * https://github.com/wang-bin/JMI
 * MIT License
 */

#include "NdkMediaCodec.hpp"
#include "android.media.MediaCodec.hpp"
#include <cassert>
#include <dlfcn.h>
#include <iostream>
#include <vector>
// TODO: jmi error/exception => media_status_t
NDKMEDIA_NS_BEGIN
using namespace jmi;
using namespace std;
// if function return type or parameter type is of (pointer to) ndk specified type, casting from or to ndk type is required to invoking ndk api
extern AMediaFormat* fromNdk(AMediaFormat* obj);
extern AMediaFormat* toNdk(const AMediaFormat* obj);
extern AMediaFormat* fromJmi(android::media::MediaFormat&& jfmt);
extern android::media::MediaFormat toJmi(const AMediaFormat* fmt);
extern AMediaCrypto* toNdk(const AMediaCrypto* obj);
extern android::media::MediaCrypto toJmi(const AMediaCrypto* obj);
extern void* mediandk_so();

struct AMediaCodec {
    AMediaCodec* ndk_; // what ptr type does not matter, but AMediaCodec* can simplify implementation
    android::media::MediaCodec jni_; //
    AMediaFormat* ofmt_;
    std::vector<java::nio::ByteBuffer> inbufs_; // jni only
    std::vector<java::nio::ByteBuffer> outbufs_; // jni only
};

AMediaCodec* fromJmi(android::media::MediaCodec&& obj)
{ // TODO: check if (!obj)?
    return new AMediaCodec{nullptr, std::move(obj)};
}

android::media::MediaCodec toJmi(const AMediaCodec* obj)
{
    if (!obj)
        return android::media::MediaCodec();
    return obj->jni_;
}

AMediaCodec* fromNdk(AMediaCodec* obj)
{
    if (!obj)
        return nullptr;
    return new AMediaCodec{obj};
}

AMediaCodec* toNdk(const AMediaCodec* obj)
{
    if (!obj)
        return nullptr;
    return obj->ndk_;
}

AMediaCodec* AMediaCodec_createCodecByName(const char *name)
{
    void* so = mediandk_so();
    if (so) {
        static auto fp = (decltype(&AMediaCodec_createCodecByName))dlsym(so, __func__);
        return fromNdk(fp(name));
    }
    auto obj = android::media::MediaCodec::createByCodecName(name);
    if (!obj)
        return nullptr;
    return fromJmi(std::move(obj));
}

AMediaCodec* AMediaCodec_createDecoderByType(const char *mime_type)
{
    void* so = mediandk_so();
    if (so) {
        static auto fp = (decltype(&AMediaCodec_createDecoderByType))dlsym(so, __func__);
        return fromNdk(fp(mime_type));
    }
    auto obj = android::media::MediaCodec::createDecoderByType(mime_type);
    if (!obj)
        return nullptr;
    return fromJmi(std::move(obj));
}

AMediaCodec* AMediaCodec_createEncoderByType(const char *mime_type)
{
    void* so = mediandk_so();
    if (so) {
        static auto fp = (decltype(&AMediaCodec_createEncoderByType))dlsym(so, __func__);
        return fromNdk(fp(mime_type));
    }
    auto obj = android::media::MediaCodec::createEncoderByType(mime_type);
    if (!obj)
        return nullptr;
    return fromJmi(std::move(obj));
}

media_status_t AMediaCodec_delete(AMediaCodec* obj)
{
    if (!obj) // required if used as smart ptr deleter
        return AMEDIA_OK;
    void* so = mediandk_so();
    if (so) {
        static auto fp = (decltype(&AMediaCodec_delete))dlsym(so, __func__);
        auto ret = fp(obj->ndk_);
        delete obj;
        return ret;
    }
    if (obj->ofmt_)
        AMediaFormat_delete(obj->ofmt_);
    if (obj->jni_) {
        obj->jni_.release();
        if (!obj->jni_.error().empty())
            std::clog << __PRETTY_FUNCTION__ << " ERROR: " << obj->jni_.error() << std::endl;
    }
    delete obj;
    return AMEDIA_OK;
}

// FIXME: null if dyload
extern "C" jobject ANativeWindow_toSurface(JNIEnv* env, ANativeWindow* window) __attribute__((weak));

media_status_t AMediaCodec_configure(AMediaCodec* obj, const AMediaFormat* format, ANativeWindow* surface, AMediaCrypto *crypto, uint32_t flags)
{
    void* so = mediandk_so();
    if (so) {
        static auto fp = (decltype(&AMediaCodec_configure))dlsym(so, __func__);
        return fp(obj->ndk_, toNdk(format), surface, toNdk(crypto), flags);
    }
// frameworks_base/native/android/native_window_jni.cpp: window=>Surface
// core/jni/android_view_Surface.cpp: Surface=>NewObject, internal ptr incStrong
    android::view::Surface s;
    JNIEnv* env = getEnv();
    if (ANativeWindow_toSurface)
        s.reset(ANativeWindow_toSurface(env, surface), env);
    else
        s.reset(env->NewLocalRef(jobject(surface)), env);  // FIXME: expected reference of kind local reference but found global reference
    obj->jni_.configure(toJmi(format), s, toJmi(crypto), flags); // FIXME: expected reference of kind local reference but found global reference
    if (obj->jni_.error().empty())
        return AMEDIA_OK;
    std::clog << __func__ << " ERROR: " << obj->jni_.error() << std::endl;
    return AMEDIA_ERROR_BASE;
}

media_status_t AMediaCodec_start(AMediaCodec* obj)
{
    void* so = mediandk_so();
    if (so) {
        static auto fp = (decltype(&AMediaCodec_start))dlsym(so, __func__);
        return fp(obj->ndk_);
    }
    obj->jni_.start();
    if (obj->jni_.error().empty())
        return AMEDIA_OK;
    std::clog << __func__ << " ERROR: " << obj->jni_.error() << std::endl;
    return AMEDIA_ERROR_BASE;
}

media_status_t AMediaCodec_stop(AMediaCodec* obj)
{
    void* so = mediandk_so();
    if (so) {
        static auto fp = (decltype(&AMediaCodec_stop))dlsym(so, __func__);
        return fp(obj->ndk_);
    }
    obj->jni_.stop();
    return AMEDIA_OK;
    if (obj->jni_.error().empty())
        return AMEDIA_OK;
    std::clog << __func__ << " ERROR: " << obj->jni_.error() << std::endl;
    return AMEDIA_ERROR_BASE;
}

media_status_t AMediaCodec_flush(AMediaCodec* obj)
{
    void* so = mediandk_so();
    if (so) {
        static auto fp = (decltype(&AMediaCodec_flush))dlsym(so, __func__);
        return fp(obj->ndk_);
    }
    obj->jni_.flush();
    if (obj->jni_.error().empty())
        return AMEDIA_OK;
    std::clog << __func__ << " ERROR: " << obj->jni_.error() << std::endl;
    return AMEDIA_ERROR_BASE;
}

uint8_t* AMediaCodec_getInputBuffer(AMediaCodec* obj, size_t idx, size_t *out_size)
{
    void* so = mediandk_so();
    if (so) {
        static auto fp = (decltype(&AMediaCodec_getInputBuffer))dlsym(so, __func__);
        return fp(obj->ndk_, idx, out_size);
    }
    if (obj->inbufs_.empty()) {
        obj->inbufs_ = obj->jni_.getInputBuffers();
        if (!obj->jni_.error().empty()) {
            std::clog << "AMediaCodec_getInputBuffer ERROR: " << obj->jni_.error() << std::endl;
            return nullptr;
        }
        std::clog << "AMediaCodec_getInputBuffer input buffer count: " << obj->inbufs_.size() << std::endl;
    }
    if (idx >= obj->inbufs_.size()) {
        std::clog << "AMediaCodec_getInputBuffer ERROR: index " << idx << " out of range " << obj->inbufs_.size() << std::endl;
        return nullptr;
    }
    java::nio::ByteBuffer& bb = obj->inbufs_[idx];
    JNIEnv *env = getEnv();
    if (out_size)
        *out_size = env->GetDirectBufferCapacity(bb);
    return (uint8_t*)env->GetDirectBufferAddress(bb);
}

uint8_t* AMediaCodec_getOutputBuffer(AMediaCodec* obj, size_t idx, size_t *out_size)
{
    void* so = mediandk_so();
    if (so) {
        static auto fp = (decltype(&AMediaCodec_getOutputBuffer))dlsym(so, __func__);
        return fp(obj->ndk_, idx, out_size);
    }
    if (obj->outbufs_.empty()) {
        obj->outbufs_ = obj->jni_.getOutputBuffers();
        if (!obj->jni_.error().empty()) {
            std::clog << "AMediaCodec_getOutputBuffer ERROR: " << obj->jni_.error() << std::endl;
            return nullptr;
        }
        std::clog << "AMediaCodec_getOutputBuffer output buffer count: " << obj->outbufs_.size() << std::endl;
    }
    if (idx >= obj->outbufs_.size()) {
        std::clog << "AMediaCodec_getOutputBuffer ERROR: index " << idx << " out of range " << obj->outbufs_.size() << std::endl;
        return nullptr;
    }
    java::nio::ByteBuffer& bb = obj->outbufs_[idx];
    JNIEnv *env = getEnv();
    if (out_size)
        *out_size = env->GetDirectBufferCapacity(bb);
    return (uint8_t*)env->GetDirectBufferAddress(bb);
}

ssize_t AMediaCodec_dequeueInputBuffer(AMediaCodec* obj, int64_t timeoutUs)
{
    void* so = mediandk_so();
    if (so) {
        static auto fp = (decltype(&AMediaCodec_dequeueInputBuffer))dlsym(so, __func__);
        return fp(obj->ndk_, timeoutUs);
    }
    auto ret = obj->jni_.dequeueInputBuffer(timeoutUs);
    if (!obj->jni_.error().empty())
        std::clog << __func__ << " ERROR: " << obj->jni_.error() << std::endl;
    return ret;
}

media_status_t AMediaCodec_queueInputBuffer(AMediaCodec* obj, size_t idx, long offset, size_t size, uint64_t time, uint32_t flags)
{
    void* so = mediandk_so();
    if (so) {
        static auto fp = (decltype(&AMediaCodec_queueInputBuffer))dlsym(so, __func__);
        return fp(obj->ndk_, idx, offset, size, time, flags);
    }
    obj->jni_.queueInputBuffer(idx, offset, size, time, flags);
    if (obj->jni_.error().empty())
        return AMEDIA_OK;
    std::clog << __func__ << " ERROR: " << obj->jni_.error() << std::endl;
    return AMEDIA_ERROR_BASE;
}

//media_status_t AMediaCodec_queueSecureInputBuffer(AMediaCodec*, size_t idx, long offset, AMediaCodecCryptoInfo*, uint64_t time, uint32_t flags);

ssize_t AMediaCodec_dequeueOutputBuffer(AMediaCodec* obj, AMediaCodecBufferInfo *info, int64_t timeoutUs)
{
    void* so = mediandk_so();
    if (so) {
        static auto fp = (decltype(&AMediaCodec_dequeueOutputBuffer))dlsym(so, __func__);
        return fp(obj->ndk_, info, timeoutUs);
    }
    android::media::MediaCodec::BufferInfo bi; // MUST be a valid object
    if (!bi.create()) {
        std::clog << "AMediaCodec_dequeueOutputBuffer ERROR: " << bi.error() << std::endl;
        return AMEDIA_ERROR_BASE;
    }
    auto ret = obj->jni_.dequeueOutputBuffer(std::ref(bi), timeoutUs);
    if (!obj->jni_.error().empty())
        std::clog << __func__ << " ERROR: " << obj->jni_.error() << std::endl;
    if (info && bi) {
        info->offset = bi.offset();
        info->size = bi.size();
        info->presentationTimeUs = bi.presentationTimeUs();
        info->flags = bi.flags();
    }
    return ret;
}

AMediaFormat* AMediaCodec_getOutputFormat(AMediaCodec* obj)
{
    void* so = mediandk_so();
    if (so) {
        static auto fp = (decltype(&AMediaCodec_getOutputFormat))dlsym(so, __func__);
        return fromNdk(fp(obj->ndk_));
    }
    obj->ofmt_ = fromJmi(std::move(obj->jni_.getOutputFormat()));
    if (obj->jni_.error().empty())
        return obj->ofmt_;
    std::clog << __func__ << " ERROR: " << obj->jni_.error() << std::endl;
    return nullptr;
}

media_status_t AMediaCodec_releaseOutputBuffer(AMediaCodec* obj, size_t idx, bool render)
{
    void* so = mediandk_so();
    if (so) {
        static auto fp = (decltype(&AMediaCodec_releaseOutputBuffer))dlsym(so, __func__);
        return fp(obj->ndk_, idx, render);
    }
    obj->jni_.releaseOutputBuffer(idx, render);
    if (obj->jni_.error().empty())
        return AMEDIA_OK;
    std::clog << __func__ << " ERROR: " << obj->jni_.error() << std::endl;
    return AMEDIA_ERROR_BASE;
}

media_status_t AMediaCodec_setOutputSurface(AMediaCodec* obj, ANativeWindow* surface)
{ // api 23
    void* so = mediandk_so();
    assert(so);
    static auto fp = (decltype(&AMediaCodec_setOutputSurface))dlsym(so, __func__);
    return fp(obj->ndk_, surface);
}

media_status_t AMediaCodec_releaseOutputBufferAtTime(AMediaCodec *obj, size_t idx, int64_t timestampNs)
{ // api 21
// jni: releaseOutputBuffer(..., timestampNs)
    void* so = mediandk_so();
    assert(so);
    static auto fp = (decltype(&AMediaCodec_releaseOutputBufferAtTime))dlsym(so, __func__);
    return fp(obj->ndk_, idx, timestampNs);
}

media_status_t AMediaCodec_createInputSurface(AMediaCodec *obj, ANativeWindow **surface)
{ // api 18
    return AMEDIA_ERROR_UNSUPPORTED;
}

media_status_t AMediaCodec_createPersistentInputSurface(ANativeWindow **surface);
media_status_t AMediaCodec_setInputSurface(AMediaCodec*, ANativeWindow *surface);
media_status_t AMediaCodec_setParameters(AMediaCodec*, const AMediaFormat* params);
media_status_t AMediaCodec_signalEndOfInputStream(AMediaCodec*);

NDKMEDIA_NS_END
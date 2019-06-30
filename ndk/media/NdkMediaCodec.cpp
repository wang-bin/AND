/*
 * AND: Android Native Dev in Modern C++ based on JMI
 * Copyright (C) 2018-2019 Wang Bin - wbsecg1@gmail.com
 * https://github.com/wang-bin/AND
 * https://github.com/wang-bin/JMI
 * MIT License
 */
// TODO: jmi error/exception => media_status_t. libhybrid?
#include "NdkMediaCodec.hpp"
#include "android.media.MediaCodec.hpp"
#include <dlfcn.h>
#include <sys/system_properties.h>
#include <iostream>
#include <vector>
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
    int api_level_ = 0;
    std::string name_;
    std::vector<java::nio::ByteBuffer> inbufs_; // jni only
    std::vector<java::nio::ByteBuffer> outbufs_; // jni only
    AMediaCodecOnAsyncNotifyCallback async_cb_{};
    void* async_cb_userdata_ = nullptr;
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
    std::clog << __PRETTY_FUNCTION__ << " via ndk: " << !!so << std::endl;
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
    std::clog << __PRETTY_FUNCTION__ << " via ndk: " << !!so << std::endl;
    if (so) {
        static auto fp = (decltype(&AMediaCodec_createDecoderByType))dlsym(so, __func__);
        return fromNdk(fp(mime_type));
    }
    auto obj = android::media::MediaCodec::createDecoderByType(mime_type); // Blocking?
    if (!obj)
        return nullptr;
    return fromJmi(std::move(obj));
}

AMediaCodec* AMediaCodec_createEncoderByType(const char *mime_type)
{
    void* so = mediandk_so();
    std::clog << __PRETTY_FUNCTION__ << " via ndk: " << !!so << std::endl;
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
    if (obj->jni_) {
        obj->jni_.release();
        if (!obj->jni_.error().empty())
            std::clog << __PRETTY_FUNCTION__ << " ERROR: " << obj->jni_.error() << std::endl;
    }
    delete obj;
    return AMEDIA_OK;
}

// null if dyload
extern "C" jobject ANativeWindow_toSurface(JNIEnv* env, ANativeWindow* window) __attribute__((weak)); // FIXME: arm64 thin lto does not support weak?

// TODO: surface=>{surface, anw}
media_status_t AMediaCodec_configure(AMediaCodec* obj, const AMediaFormat* format, ANativeWindow* surface, AMediaCrypto *crypto, uint32_t flags)
{
    char v[PROP_VALUE_MAX+1];
    __system_property_get("ro.build.version.sdk", v); //AConfiguration_getSdkVersion
    obj->api_level_ = std::max(atoi(v), 9); // since android 2.3, api 9

    void* so = mediandk_so();
    if (so) {
        static auto fp = (decltype(&AMediaCodec_configure))dlsym(so, __func__);
        return fp(obj->ndk_, toNdk(format), surface, toNdk(crypto), flags);
    }
// frameworks_base/native/android/native_window_jni.cpp: window=>Surface
// core/jni/android_view_Surface.cpp: Surface=>NewObject, internal ptr incStrong
    android::view::Surface s;
    JNIEnv* env = getEnv();
    static void* libandroid_so = dlopen("libandroid.so", RTLD_NOLOAD|RTLD_LOCAL);
    using ANativeWindow_toSurface_t = jobject(*)(JNIEnv* env, ANativeWindow* window);
    static auto ANativeWindow_toSurface = (ANativeWindow_toSurface_t)dlsym(libandroid_so ? libandroid_so : RTLD_DEFAULT, "ANativeWindow_toSurface");
    if (surface) {
        if (ANativeWindow_toSurface)
            s.reset(ANativeWindow_toSurface(env, surface), env);
        else
            s.reset(env->NewLocalRef(jobject(surface)), env);  // FIXME: expected reference of kind local reference but found global reference
    }
    obj->jni_.configure(toJmi(format), s, toJmi(crypto), flags);
    if (obj->jni_.error().empty())
        return AMEDIA_OK;
    std::clog << __PRETTY_FUNCTION__ << " ERROR: " << obj->jni_.error() << std::endl;
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
    std::clog << __PRETTY_FUNCTION__ << " ERROR: " << obj->jni_.error() << std::endl;
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
    std::clog << __PRETTY_FUNCTION__ << " ERROR: " << obj->jni_.error() << std::endl;
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
    std::clog << __PRETTY_FUNCTION__ << " ERROR: " << obj->jni_.error() << std::endl;
    return AMEDIA_ERROR_BASE;
}

uint8_t* AMediaCodec_getInputBuffer(AMediaCodec* obj, size_t idx, size_t *out_size)
{
    void* so = mediandk_so();
    if (so) {
        static auto fp = (decltype(&AMediaCodec_getInputBuffer))dlsym(so, __func__);
        return fp(obj->ndk_, idx, out_size);
    }
    if (obj->api_level_ >= 21) {
        const auto bb = obj->jni_.getInputBuffer((jint)idx);
        if (!obj->jni_.error().empty()) {
            std::clog << "AMediaCodec_getInputBuffer ERROR: " << obj->jni_.error() << std::endl;
            return nullptr;
        }
        JNIEnv *env = getEnv();
        if (out_size)
            *out_size = env->GetDirectBufferCapacity(bb);
        return (uint8_t*)env->GetDirectBufferAddress(bb);
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
    if (obj->api_level_ >= 21) {
        const auto bb = obj->jni_.getOutputBuffer((jint)idx);
        if (!obj->jni_.error().empty()) {
            std::clog << "AMediaCodec_getOutputBuffer ERROR: " << obj->jni_.error() << std::endl;
            return nullptr;
        }
        JNIEnv *env = getEnv();
        if (out_size)
            *out_size = env->GetDirectBufferCapacity(bb);
        return (uint8_t*)env->GetDirectBufferAddress(bb);
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
        std::clog << __PRETTY_FUNCTION__ << " ERROR: " << obj->jni_.error() << std::endl;
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
    std::clog << __PRETTY_FUNCTION__ << " ERROR: " << obj->jni_.error() << std::endl;
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
        std::clog << __PRETTY_FUNCTION__ << " ERROR: " << obj->jni_.error() << std::endl;
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
    auto fmt = fromJmi(std::move(obj->jni_.getOutputFormat()));
    if (obj->jni_.error().empty())
        return fmt;
    std::clog << __PRETTY_FUNCTION__ << " ERROR: " << obj->jni_.error() << std::endl;
    return nullptr;
}

media_status_t AMediaCodec_releaseOutputBuffer(AMediaCodec* obj, size_t idx, bool render)
{
    void* so = mediandk_so();
    if (so) {
        static auto fp = (decltype(&AMediaCodec_releaseOutputBuffer))dlsym(so, __func__);
        return fp(obj->ndk_, idx, render);
    }
    obj->jni_.releaseOutputBuffer(idx, (jboolean)render);
    if (obj->jni_.error().empty())
        return AMEDIA_OK;
    std::clog << __PRETTY_FUNCTION__ << " ERROR: " << obj->jni_.error() << std::endl;
    return AMEDIA_ERROR_BASE;
}

media_status_t AMediaCodec_setOutputSurface(AMediaCodec* obj, ANativeWindow* surface)
{
    void* so = mediandk_so();
    if (so) {
        static auto fp = (decltype(&AMediaCodec_setOutputSurface))dlsym(so, __func__);
        return fp(obj->ndk_, surface);
    }
    return AMEDIA_ERROR_UNSUPPORTED;
}

media_status_t AMediaCodec_releaseOutputBufferAtTime(AMediaCodec *obj, size_t idx, int64_t timestampNs)
{
    void* so = mediandk_so();
    if (so) {
        static auto fp = (decltype(&AMediaCodec_releaseOutputBufferAtTime))dlsym(so, __func__);
        return fp(obj->ndk_, idx, timestampNs);
    }
    obj->jni_.releaseOutputBuffer(idx, jlong(timestampNs)); // api 21
    if (obj->jni_.error().empty())
        return AMEDIA_OK;
    std::clog << __PRETTY_FUNCTION__ << " ERROR: " << obj->jni_.error() << std::endl;
    return AMEDIA_ERROR_BASE;
}

media_status_t AMediaCodec_createInputSurface(AMediaCodec *obj, ANativeWindow **surface)
{ // TODO: java api 18, ndk 26
    return AMEDIA_ERROR_UNSUPPORTED;
}

media_status_t AMediaCodec_createPersistentInputSurface(ANativeWindow **surface);
media_status_t AMediaCodec_setInputSurface(AMediaCodec*, ANativeWindow *surface);
media_status_t AMediaCodec_setParameters(AMediaCodec*, const AMediaFormat* params);

media_status_t AMediaCodec_signalEndOfInputStream(AMediaCodec* obj) // ndk 26, java 18
{
    auto so = mediandk_so();
    if (so) {
        static auto fp = (decltype(&AMediaCodec_signalEndOfInputStream))dlsym(so, __func__);
        if (!fp)
            return AMEDIA_ERROR_UNSUPPORTED;
        return fp(obj->ndk_);
    }
    obj->jni_.signalEndOfInputStream();
    if (!obj->jni_.error().empty()) {
        std::clog << __PRETTY_FUNCTION__ << " ERROR: " << obj->jni_.error() << std::endl;
        return AMEDIA_ERROR_UNKNOWN;
    }
    return AMEDIA_OK;
}

AMediaFormat* AMediaCodec_getBufferFormat(AMediaCodec* obj, size_t index)
{ // ndk 28, java 21
    void* so = mediandk_so();
    if (so) {
        static auto fp = (decltype(&AMediaCodec_getBufferFormat))dlsym(so, __func__);
        if (!fp)
            return nullptr;
        return fromNdk(fp(obj->ndk_, index));
    }
    auto fmt = fromJmi(std::move(obj->jni_.getOutputFormat((jint)index)));
    if (obj->jni_.error().empty())
        return fmt;
    std::clog << __PRETTY_FUNCTION__ << " ERROR: " << obj->jni_.error() << std::endl;
    return nullptr;
}

media_status_t AMediaCodec_getName(AMediaCodec* obj, char** out_name)
{ // ndk 28, java 18
    void* so = mediandk_so();
    if (so) {
        static auto fp = (decltype(&AMediaCodec_getName))dlsym(so, __func__);
        if (!fp)
            return AMEDIA_ERROR_UNSUPPORTED;
        return fp(obj->ndk_, out_name);
    }
    obj->name_ = std::move(obj->jni_.getName());
    if (obj->jni_.error().empty()) {
        *out_name = &obj->name_[0];
        return AMEDIA_OK;
    }
    std::clog << __PRETTY_FUNCTION__ << " ERROR: " << obj->jni_.error() << std::endl;
    return AMEDIA_ERROR_BASE;
}

void AMediaCodec_releaseName(AMediaCodec* obj, char* name)
{ // ndk 28
    void* so = mediandk_so();
    if (so) {
        static auto fp = (decltype(&AMediaCodec_releaseName))dlsym(so, __func__);
        if (!fp)
            return;
        return fp(obj->ndk_, name);
    }
    obj->name_.clear();
}

media_status_t AMediaCodec_setAsyncNotifyCallback(AMediaCodec* obj, AMediaCodecOnAsyncNotifyCallback callback, void *userdata)
{ // ndk 28
    auto so = mediandk_so();
    if (!so)
        return AMEDIA_ERROR_UNSUPPORTED;
    static auto fp = (decltype(&AMediaCodec_setAsyncNotifyCallback))dlsym(so, __func__);
    if (!fp)
        return AMEDIA_ERROR_UNSUPPORTED;
    obj->async_cb_ = callback;
    obj->async_cb_userdata_ = userdata;
    AMediaCodecOnAsyncNotifyCallback cb;
    // codec, format etc. in callback parameter from ndk are ndk objects, we must convert them to our c++ objects
    cb.onAsyncInputAvailable = [](AMediaCodec *codec, void *userdata, int32_t index) {
        auto obj = static_cast<AMediaCodec*>(userdata);
        obj->async_cb_.onAsyncInputAvailable(fromNdk(codec), obj->async_cb_userdata_, index);
    };
    cb.onAsyncOutputAvailable = [](AMediaCodec *codec, void *userdata, int32_t index, AMediaCodecBufferInfo *bufferInfo) {
        auto obj = static_cast<AMediaCodec*>(userdata);
        obj->async_cb_.onAsyncOutputAvailable(fromNdk(codec), obj->async_cb_userdata_, index, bufferInfo);
    };
    cb.onAsyncFormatChanged = [](AMediaCodec *codec, void *userdata, AMediaFormat *format) {
        auto obj = static_cast<AMediaCodec*>(userdata);
        obj->async_cb_.onAsyncFormatChanged(fromNdk(codec), obj->async_cb_userdata_, fromNdk(format));
    };
    cb.onAsyncError = [](AMediaCodec *codec, void *userdata, media_status_t error, int32_t actionCode, const char *detail) {
        auto obj = static_cast<AMediaCodec*>(userdata);
        obj->async_cb_.onAsyncError(fromNdk(codec), obj->async_cb_userdata_, error, actionCode, detail);
    };
    return fp(obj->ndk_, cb, obj);
}

//media_status_t AMediaCodec_releaseCrypto(AMediaCodec*);

AMediaFormat* AMediaCodec_getInputFormat(AMediaCodec* obj)
{ // ndk 28, java 21
    auto so = mediandk_so();
    if (so) {
        static auto fp = (decltype(&AMediaCodec_getInputFormat))dlsym(so, __func__);
        if (!fp)
            return nullptr;
        return fromNdk(fp(obj->ndk_));
    }
    auto fmt = fromJmi(std::move(obj->jni_.getInputFormat()));
    if (obj->jni_.error().empty())
        return fmt;
    std::clog << __PRETTY_FUNCTION__ << " ERROR: " << obj->jni_.error() << std::endl;
    return nullptr;
}

bool AMediaCodecActionCode_isRecoverable(int32_t actionCode)
{
    auto so = mediandk_so();
    if (!so)
        return false;
    static auto fp = (decltype(&AMediaCodecActionCode_isRecoverable))dlsym(so, __func__);
    if (!fp) {
        std::clog << "WARNING: " << __func__ << " is not supported" << std::endl;
        return false;
    }
    return fp(actionCode);
}

bool AMediaCodecActionCode_isTransient(int32_t actionCode)
{
    auto so = mediandk_so();
    if (!so)
        return false;
    static auto fp = (decltype(&AMediaCodecActionCode_isRecoverable))dlsym(so, __func__);
    if (!fp) {
        std::clog << "WARNING: " << __func__ << " is not supported" << std::endl;
        return false;
    }
    return fp(actionCode);
}
NDKMEDIA_NS_END
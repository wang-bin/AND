/*
 * AND: Android Native Dev in Modern C++ based on JMI
 * Copyright (C) 2018-2019 Wang Bin - wbsecg1@gmail.com
 * https://github.com/wang-bin/AND
 * https://github.com/wang-bin/JMI
 * MIT License
 */

#include "NdkMediaFormat.hpp"
#include "android.media.MediaFormat.hpp"
#include <dlfcn.h>
#include <iostream>

NDKMEDIA_NS_BEGIN
using namespace jmi;

static bool sEmulated = false;
void* mediandk_so() {
    if (sEmulated)
        return nullptr;
    static void* dso = dlopen("libmediandk.so", RTLD_LAZY|RTLD_LOCAL);
    return dso;
}

struct AMediaFormat {
    AMediaFormat* ndk_; // what ptr type does not matter, but AMediaFormat* can simplify implementation
    android::media::MediaFormat jni_; //
    std::string str_;
    std::string get_str_;
};

AMediaFormat* fromJmi(android::media::MediaFormat&& obj)
{
    return new AMediaFormat{nullptr, std::move(obj)};
}

android::media::MediaFormat toJmi(const AMediaFormat* obj)
{
    if (!obj)
        return android::media::MediaFormat();
    return obj->jni_;
}

AMediaFormat* fromNdk(AMediaFormat* obj)
{
    if (!obj)
        return nullptr;
    return new AMediaFormat{obj};;
}

AMediaFormat* toNdk(const AMediaFormat* obj)
{
    if (!obj)
        return nullptr;
    return obj->ndk_;
}

AMediaFormat *AMediaFormat_new() {
    if (!mediandk_so()) {
        android::media::MediaFormat obj;
        if (!obj.create())
            return nullptr;
        return fromJmi(std::move(obj));
    }
    static auto fp = (decltype(&AMediaFormat_new))dlsym(mediandk_so(), __func__);
    return fromNdk(fp());
}

media_status_t AMediaFormat_delete(AMediaFormat* obj) {
    if (!obj) // required if used as smart ptr deleter
        return AMEDIA_OK;
    void* so = mediandk_so();
    if (!so) {
        delete obj;
        return AMEDIA_OK;
    }
    static auto fp = (decltype(&AMediaFormat_delete))dlsym(so, __func__);
    auto ret = fp(obj->ndk_);
    delete obj;
    return ret;
}

const char* AMediaFormat_toString(AMediaFormat* obj) {
    void* so = mediandk_so();
    if (so) {
        static auto fp = (decltype(&AMediaFormat_toString))dlsym(so, __func__);
        return fp(obj->ndk_);
    }
    obj->str_ = obj->jni_.toString(); // owned by format
    if (obj->jni_.error().empty())
        return obj->str_.data();
    std::clog << __func__ << " ERROR: " << obj->jni_.error() << std::endl;
    return nullptr;
}

bool AMediaFormat_getInt32(AMediaFormat* obj, const char *name, int32_t *out)
{
    void* so = mediandk_so();
    if (so) {
        static void* fp = dlsym(so, __func__);
        return decltype(&AMediaFormat_getInt32)(fp)(obj->ndk_, name, out);
    }
    if (!obj->jni_.containsKey(name))
        return false;
    *out = obj->jni_.getInteger(name);
    if (obj->jni_.error().empty())
        return true;
    std::clog << __func__ << " ERROR: " << obj->jni_.error() << std::endl;
    return false;
}

bool AMediaFormat_getInt64(AMediaFormat* obj, const char *name, int64_t *out)
{
    void* so = mediandk_so();
    if (so) {
        static void* fp = dlsym(mediandk_so(), __func__);
        return decltype(&AMediaFormat_getInt64)(fp)(obj->ndk_, name, out);
    }
    if (!obj->jni_.containsKey(name))
        return false;
    *out = obj->jni_.getLong(name);
    if (obj->jni_.error().empty())
        return true;
    std::clog << __func__ << " ERROR: " << obj->jni_.error() << std::endl;
    return false;
}

bool AMediaFormat_getFloat(AMediaFormat* obj, const char *name, float *out)
{
    void* so = mediandk_so();
    if (so) {
        static void* fp = dlsym(mediandk_so(), __func__);
        return decltype(&AMediaFormat_getFloat)(fp)(obj->ndk_, name, out);
    }
    if (!obj->jni_.containsKey(name))
        return false;
    *out = obj->jni_.getFloat(name);
    if (obj->jni_.error().empty())
        return true;
    std::clog << __func__ << " ERROR: " << obj->jni_.error() << std::endl;
    return false;
}

bool AMediaFormat_getBuffer(AMediaFormat* obj, const char *name, void** data, size_t *size)
{
    void* so = mediandk_so();
    if (so) {
        static void* fp = dlsym(mediandk_so(), __func__);
        return decltype(&AMediaFormat_getBuffer)(fp)(obj->ndk_, name, data, size);
    }
    if (!obj->jni_.containsKey(name))
        return false;
    auto ret = obj->jni_.getByteBuffer(name);
    if (!obj->jni_.error().empty()) {
        std::clog << __func__ << " ERROR: " << obj->jni_.error() << std::endl;
        return false;
    }
    JNIEnv *env = getEnv();
    *data = env->GetDirectBufferAddress(ret);
    *size = env->GetDirectBufferCapacity(ret);
    return true;
}

bool AMediaFormat_getString(AMediaFormat* obj, const char *name, const char **out)
{
    void* so = mediandk_so();
    if (so) {
        static auto fp = (decltype(&AMediaFormat_getString))dlsym(so, __func__);
        return fp(obj->ndk_, name, out);
    }
    if (!obj->jni_.containsKey(name))
        return false;
    obj->get_str_ = obj->jni_.getString(name); // owned by format, keep valid until next call
    *out = obj->get_str_.data();
    if (obj->jni_.error().empty())
        return true;
    *out = nullptr;
    std::clog << __func__ << " ERROR: " << obj->jni_.error() << std::endl;
    return false;
}

void AMediaFormat_setInt32(AMediaFormat* obj, const char* name, int32_t value)
{
    void* so = mediandk_so();
    if (so) {
        static auto fp = (decltype(&AMediaFormat_setInt32))dlsym(so, __func__);
        return fp(obj->ndk_, name, value);
    }
    obj->jni_.setInteger(name, value);
    if (!obj->jni_.error().empty())
        std::clog << __func__ << " ERROR: " << obj->jni_.error() << std::endl;
}

void AMediaFormat_setInt64(AMediaFormat* obj, const char* name, int64_t value)
{
    void* so = mediandk_so();
    if (so) {
        static auto fp = (decltype(&AMediaFormat_setInt64))dlsym(so, __func__);
        return fp(obj->ndk_, name, value);
    }
    obj->jni_.setLong(name, value);
    if (!obj->jni_.error().empty())
        std::clog << __func__ << " ERROR: " << obj->jni_.error() << std::endl;
}

void AMediaFormat_setFloat(AMediaFormat* obj, const char* name, float value)
{
    void* so = mediandk_so();
    if (so) {
        static auto fp = (decltype(&AMediaFormat_setFloat))dlsym(so, __func__);
        return fp(obj->ndk_, name, value);
    }
    obj->jni_.setFloat(name, value);
    if (!obj->jni_.error().empty())
        std::clog << __func__ << " ERROR: " << obj->jni_.error() << std::endl;
}

void AMediaFormat_setString(AMediaFormat* obj, const char* name, const char* value)
{
    void* so = mediandk_so();
    if (so) {
        static auto fp = (decltype(&AMediaFormat_setString))dlsym(so, __func__);
        return fp(obj->ndk_, name, value);
    }
    obj->jni_.setString(name, value);
    if (!obj->jni_.error().empty())
        std::clog << __func__ << " ERROR: " << obj->jni_.error() << std::endl;
}

void AMediaFormat_setBuffer(AMediaFormat* obj, const char* name, void* data, size_t size)
{
    void* so = mediandk_so();
    if (so) {
        static auto fp = (decltype(&AMediaFormat_setBuffer))dlsym(so, __func__);
        fp(obj->ndk_, name, data, size);
        return;
    }
    LocalRef dbb = getEnv()->NewDirectByteBuffer(data, size);
    obj->jni_.setByteBuffer(name, java::nio::ByteBuffer(std::move(dbb)));
    if (!obj->jni_.error().empty())
        std::clog << __func__ << " ERROR: " << obj->jni_.error() << std::endl;
}

bool AMediaFormat_getDouble(AMediaFormat* obj, const char *name, double *out)
{
    void* so = mediandk_so();
    if (!so)
        return false;
    static auto fp = (decltype(&AMediaFormat_getDouble))dlsym(so, __func__);
    if (!fp)
        return false;
    return fp(obj->ndk_, name, out);
}

bool AMediaFormat_getRect(AMediaFormat* obj, const char *name, int32_t *left, int32_t *top, int32_t *right, int32_t *bottom)
{
    void* so = mediandk_so();
    if (!so)
        return false;
    static auto fp = (decltype(&AMediaFormat_getRect))dlsym(so, __func__);
    if (!fp)
        return false;
    return fp(obj->ndk_, name, left, top, right, bottom);
}

void AMediaFormat_setDouble(AMediaFormat* obj, const char* name, double value)
{
    void* so = mediandk_so();
    if (!so)
        return;
    static auto fp = (decltype(&AMediaFormat_setDouble))dlsym(so, __func__);
    if (!fp)
        fp(obj->ndk_, name, value);
}

void AMediaFormat_setSize(AMediaFormat* obj, const char* name, size_t value)
{
    void* so = mediandk_so();
    if (!so)
        return;
    static auto fp = (decltype(&AMediaFormat_setSize))dlsym(so, __func__);
    if (fp)
        return fp(obj->ndk_, name, value);
}

void AMediaFormat_setRect(AMediaFormat* obj, const char* name, int32_t left, int32_t top, int32_t right, int32_t bottom)
{
    void* so = mediandk_so();
    if (!so)
        return;
    static auto fp = (decltype(&AMediaFormat_setRect))dlsym(so, __func__);
    if (fp)
        return fp(obj->ndk_, name, left, top, right, bottom);
}
NDKMEDIA_NS_END

// NOTE: global, all codecs MUST be the same value, otherwise it's UB
void mediandk_set_emulated(bool value) {
    NDKMEDIA_NS::sEmulated = value;
}

bool mediandk_is_emulated() { // set by user, or runtime does not exist
    return !NDKMEDIA_NS::mediandk_so();
}

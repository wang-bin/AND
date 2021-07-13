/*
 * AND: Android Native Dev in Modern C++ based on JMI
 * Copyright (C) 2018-2021 Wang Bin - wbsecg1@gmail.com
 * https://github.com/wang-bin/AND
 * https://github.com/wang-bin/JMI
 * MIT License
 */

#pragma once
#include "jmi/jmi.h"

namespace jmi {
namespace android {
namespace media {
class MediaCrypto : public jmi::JObject<MediaCrypto> { // inherits JObject so that it can be a return type like primitive types
public:
    using Base = jmi::JObject<MediaCrypto>;
    using Base::Base; // inherits ctors
    static constexpr auto name() { return JMISTR("android/media/MediaCrypto");} // required if derive from JObject<>
    //static jboolean isCryptoSchemeSupported(UUID uuid);
    void release();
    jboolean requiresSecureDecoderComponent(const char* mime) const;
};
} // namespace media
} // namespace android
} // namespace jmi
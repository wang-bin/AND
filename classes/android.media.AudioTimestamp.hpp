/*
 * AND: Android Native Dev in Modern C++ based on JMI
 * Copyright (C) 2026 Wang Bin - wbsecg1@gmail.com
 * AI assisted
 * https://github.com/wang-bin/AND
 * https://github.com/wang-bin/JMI
 * MIT License
 */

#pragma once
#include "jmi/jmi.h"

namespace jmi {
namespace android {
namespace media {
class AudioTimestamp : public jmi::JObject<AudioTimestamp>
{
public:
    using Base = jmi::JObject<AudioTimestamp>;
    using Base::Base;
    static constexpr auto name() { return JMISTR("android/media/AudioTimestamp"); }
    // DO NOT forget to call create()
    jlong framePosition() const;
    jlong nanoTime() const;
};
} // namespace media
} // namespace android
} // namespace jmi

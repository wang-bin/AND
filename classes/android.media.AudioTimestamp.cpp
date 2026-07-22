/*
 * AND: Android Native Dev in Modern C++ based on JMI
 * Copyright (C) 2026 Wang Bin - wbsecg1@gmail.com
 * AI assisted
 * https://github.com/wang-bin/AND
 * https://github.com/wang-bin/JMI
 * MIT License
 */

#include "android.media.AudioTimestamp.hpp"
#include "JMIUtils.hpp"

namespace jmi {
namespace android {
namespace media {
JMI_DEFINE_FIELD_CONST(jlong, AudioTimestamp::framePosition)
JMI_DEFINE_FIELD_CONST(jlong, AudioTimestamp::nanoTime)
} // namespace media
} // namespace android
} // namespace jmi

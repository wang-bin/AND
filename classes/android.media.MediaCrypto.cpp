/*
 * AND: Android Native Dev in Modern C++ based on JMI
 * Copyright (C) 2018 Wang Bin - wbsecg1@gmail.com
 * https://github.com/wang-bin/AND
 * https://github.com/wang-bin/JMI
 * MIT License
 */

#include "android.media.MediaCrypto.hpp"
#include "JMIUtils.hpp"
namespace jmi {
namespace android {
namespace media {
JMI_DEFINE_CONST(jboolean, MediaCrypto::requiresSecureDecoderComponent, JMI_ARG1(const char*))
JMI_DEFINE(void, MediaCrypto::release, JMI_ARG0())
} // namespace media
} // namespace android
} // namespace jmi
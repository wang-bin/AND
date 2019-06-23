/*
 * AND: Android Native Dev in Modern C++ based on JMI
 * Copyright (C) 2018-2019 Wang Bin - wbsecg1@gmail.com
 * https://github.com/wang-bin/AND
 * https://github.com/wang-bin/JMI
 * MIT License
 */
#include "android.media.MediaCodecList.hpp"
#include "JMIUtils.hpp"
namespace jmi {
namespace android {
namespace media {
JMI_DEFINE_STATIC(jint, MediaCodecList::getCodecCount, JMI_ARG0())
JMI_DEFINE_STATIC(MediaCodecInfo, MediaCodecList::getCodecInfoAt, JMI_ARG1(jint))
JMI_DEFINE_CONST(std::string, MediaCodecList::findDecoderForFormat, JMI_ARG1(MediaFormat))
JMI_DEFINE_CONST(std::string, MediaCodecList::findEncoderForFormat, JMI_ARG1(MediaFormat))
JMI_DEFINE_CONST(std::vector<MediaCodecInfo>, MediaCodecList::getCodecInfos, JMI_ARG0())
} // namespace media
} // namespace android
} // namespace jmi
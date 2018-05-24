/*
 * AND: Android Native Dev in Modern C++ based on JMI
 * Copyright (C) 2018 Wang Bin - wbsecg1@gmail.com
 * https://github.com/wang-bin/AND
 * https://github.com/wang-bin/JMI
 * MIT License
 */

#include "android.media.MediaFormat.hpp"
#include "java.nio.ByteBuffer.hpp"
#include "JMIUtils.hpp"
#include <iostream>
namespace jmi {
namespace android {
namespace media {
JMI_DEFINE_CONST(std::string, MediaFormat::toString, JMI_ARG0())
JMI_DEFINE_CONST(java::nio::ByteBuffer, MediaFormat::getByteBuffer, JMI_ARG1(const char*))
JMI_DEFINE_CONST(jboolean, MediaFormat::containsKey, JMI_ARG1(const char*))
JMI_DEFINE_CONST(jfloat, MediaFormat::getFloat, JMI_ARG1(const char*))
JMI_DEFINE_CONST(jint, MediaFormat::getInteger, JMI_ARG1(const char*))
JMI_DEFINE_CONST(jlong, MediaFormat::getLong, JMI_ARG1(const char*))
JMI_DEFINE_CONST(std::string, MediaFormat::getString, JMI_ARG1(const char*))
JMI_DEFINE(void, MediaFormat::setByteBuffer, JMI_ARG2(const char*, const java::nio::ByteBuffer&))
JMI_DEFINE(void, MediaFormat::setFloat, JMI_ARG2(const char*, jfloat))
JMI_DEFINE(void, MediaFormat::setInteger, JMI_ARG2(const char*, jint))
JMI_DEFINE(void, MediaFormat::setLong, JMI_ARG2(const char*, jlong))
JMI_DEFINE(void, MediaFormat::setString, JMI_ARG2(const char*, const char*))
} // namespace media
} // namespace android
} // namespace jmi
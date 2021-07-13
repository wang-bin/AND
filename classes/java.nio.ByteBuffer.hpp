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
namespace java {
namespace nio {

class ByteBuffer : public jmi::JObject<ByteBuffer>
{
public:
    using Base = jmi::JObject<ByteBuffer>;
    using Base::Base;
    static constexpr auto name() { return JMISTR("java/nio/ByteBuffer");}
};
} // namespace nio
} // namespace java
} // namespace jmi
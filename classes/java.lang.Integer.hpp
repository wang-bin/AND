/*
 * AND: Android Native Dev in Modern C++ based on JMI
 * Copyright (C) 2018-2026 Wang Bin - wbsecg1@gmail.com
 * https://github.com/wang-bin/AND
 * https://github.com/wang-bin/JMI
 * MIT License
 */

#pragma once
/*
public final class Integer extends Number implements Comparable<Integer> {
    public int intValue();
}
*/
#include "java.lang.Object.hpp"

namespace jmi {
namespace java {
namespace lang {

class Integer final: public jmi::JObject<Integer> {
public:
    using Base = jmi::JObject<Integer>;
    using Base::Base;
    static constexpr auto name() { return JMISTR("java/lang/Integer"); }
    jint intValue() const;
};

} // namespace lang
} // namespace java
} // namespace jmi

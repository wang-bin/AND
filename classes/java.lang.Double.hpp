/*
 * AND: Android Native Dev in Modern C++ based on JMI
 * Copyright (C) 2018-2026 Wang Bin - wbsecg1@gmail.com
 * https://github.com/wang-bin/AND
 * https://github.com/wang-bin/JMI
 * MIT License
 */

#pragma once
/*
public final class Double extends Number implements Comparable<Double> {
    public double doubleValue();
}
*/
#include "java.lang.Object.hpp"

namespace jmi {
namespace java {
namespace lang {

class Double final: public jmi::JObject<Double> {
public:
    using Base = jmi::JObject<Double>;
    using Base::Base;
    static constexpr auto name() { return JMISTR("java/lang/Double"); }
    jdouble doubleValue() const;
};

} // namespace lang
} // namespace java
} // namespace jmi

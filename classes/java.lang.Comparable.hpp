/*
 * AND: Android Native Dev in Modern C++ based on JMI
 * Copyright (C) 2018-2026 Wang Bin - wbsecg1@gmail.com
 * https://github.com/wang-bin/AND
 * https://github.com/wang-bin/JMI
 * MIT License
 */

#pragma once
/*
public interface Comparable<T> {
    int compareTo(T other);
}
*/
#include "java.lang.Object.hpp"

namespace jmi {
namespace java {
namespace lang {

class Comparable final: public jmi::JObject<Comparable> {
public:
    using Base = jmi::JObject<Comparable>;
    using Base::Base;
    static constexpr auto name() { return JMISTR("java/lang/Comparable"); }
    jint compareTo(const Object& other) const;
};

} // namespace lang
} // namespace java
} // namespace jmi

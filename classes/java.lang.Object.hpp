/*
 * AND: Android Native Dev in Modern C++ based on JMI
 * Copyright (C) 2018-2026 Wang Bin - wbsecg1@gmail.com
 * https://github.com/wang-bin/AND
 * https://github.com/wang-bin/JMI
 * MIT License
 */

#pragma once
/*
public class Object {
}
*/
#include "jmi/jmi.h"

namespace jmi {
namespace java {
namespace lang {

class Object final: public jmi::JObject<Object> {
public:
    using Base = jmi::JObject<Object>;
    using Base::Base;
    static constexpr auto name() { return JMISTR("java/lang/Object"); }
};

} // namespace lang
} // namespace java
} // namespace jmi

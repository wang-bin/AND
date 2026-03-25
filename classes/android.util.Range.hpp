
#pragma once
/*
public final class Range<T extends Comparable<? super T>> {
    public Range(final T lower, final T upper);
    public static <T extends Comparable<? super T>> Range<T> create(final T lower, final T upper);
    public T getLower();
    public T getUpper();
    public boolean contains(T value);
    public boolean contains(Range<T> range);
    public T clamp(T value);
    public Range<T> intersect(Range<T> range);
    public Range<T> intersect(T lower, T upper);
    public Range<T> extend(Range<T> range);
    public Range<T> extend(T lower, T upper);
    public Range<T> extend(T value);
};
*/
#include "java.lang.Comparable.hpp"
#include "java.lang.Integer.hpp"
#include "java.lang.Double.hpp"
#include "jmi/jmi.h"
#include <type_traits>

namespace jmi {
namespace android {
namespace util {

class Range final: public jmi::JObject<Range> {
public:
    using Base = jmi::JObject<Range>;
    using Base::Base;
    static constexpr auto name() { return JMISTR("android/util/Range"); }
    java::lang::Comparable getLower() const;
    java::lang::Comparable getUpper() const;

    template<typename T>
    T getLower() const {
        const auto obj = getLower();
        if (!obj) // don't forget to check error()
            return T{};
        if constexpr (std::is_same_v<T, jint>) { // JObject holds global ref
            return java::lang::Integer(obj, false).intValue();
        } else if constexpr (std::is_same_v<T, jdouble>) {
            return java::lang::Double(obj, false).doubleValue();
        } else {
            static_assert(!sizeof(T*), "Unsupported Range value type");
        }
    }

    template<typename T>
    T getUpper() const {
        const auto obj = getUpper();
        if (!obj) // don't forget to check error()
            return T{};
        if constexpr (std::is_same_v<T, jint>) {
            return java::lang::Integer(obj, false).intValue();
        } else if constexpr (std::is_same_v<T, jdouble>) {
            return java::lang::Double(obj, false).doubleValue();
        } else {
            static_assert(!sizeof(T*), "Unsupported Range value type");
        }
    }
};

} // namespace util
} // namespace android
} // namespace jmi
/*
 * AND: Android Native Dev in Modern C++ based on JMI
 * Copyright (C) 2026 Wang Bin - wbsecg1@gmail.com
 * https://github.com/wang-bin/AND
 * https://github.com/wang-bin/JMI
 * MIT License
 */

#pragma once

#include "../classes/JMIUtils.hpp"

#ifndef NDKCOMPAT_API_DECL
#define NDKCOMPAT_API_DECL
#endif

#define NDKCOMPAT_DEFINE_VOID(name, ...) JMI_EXPAND(NDKCOMPAT_DEFINE_VOID_(name, __VA_ARGS__))
#define NDKCOMPAT_DEFINE_VOID_(name, ARG_T, ARG_T_V, ARG_V) \
    extern "C" NDKCOMPAT_API_DECL void name ARG_T_V \
    { \
        static const auto fp = reinterpret_cast<decltype(&(name))>(resolve(#name)); \
        if (fp) \
            fp ARG_V; \
    }

#define NDKCOMPAT_DEFINE_RET(type, name, fail_ret, ...) JMI_EXPAND(NDKCOMPAT_DEFINE_RET_(type, name, fail_ret, __VA_ARGS__))
#define NDKCOMPAT_DEFINE_RET_(type, name, fail_ret, ARG_T, ARG_T_V, ARG_V) \
    extern "C" NDKCOMPAT_API_DECL type name ARG_T_V \
    { \
        static const auto fp = reinterpret_cast<decltype(&(name))>(resolve(#name)); \
        if (fp) \
            return fp ARG_V; \
        return fail_ret; \
    }

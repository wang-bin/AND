/*
 * AND: Android Native Dev in Modern C++ based on JMI
 * Copyright (C) 2018 Wang Bin - wbsecg1@gmail.com
 * https://github.com/wang-bin/AND
 * https://github.com/wang-bin/JMI
 * MIT License
 */

#pragma once

#define JMI_ARG0() (), (), ()
#define JMI_ARG1(P1) (P1), (P1 p1), (p1)
#define JMI_ARG2(P1, P2) (P1, P2), (P1 p1, P2 p2), (p1, p2)
#define JMI_ARG3(P1, P2, P3) (P1, P2, P3), (P1 p1, P2 p2, P3 p3), (p1, p2, p3)
#define JMI_ARG4(P1, P2, P3, P4) (P1, P2, P3, P4), (P1 p1, P2 p2, P3 p3, P4 p4), (p1, p2, p3, p4)
#define JMI_ARG5(P1, P2, P3, P4, P5) (P1, P2, P3, P4, P5), (P1 p1, P2 p2, P3 p3, P4 p4, P5 p5), (p1, p2, p3, p4, p5)

#define JMI_EXPAND(expr) expr
#define JMI_DEFINE(R, name, ...) JMI_EXPAND(JMI_DEFINE_T_V_(R, name, __VA_ARGS__)) /* not ##__VA_ARGS__ !*/
#define JMI_DEFINE_CONST(R, name, ...) JMI_EXPAND(JMI_DEFINE_T_V_CONST_(R, name, __VA_ARGS__)) /* not ##__VA_ARGS__ !*/
#define JMI_DEFINE_STATIC(R, name, ...) JMI_EXPAND(JMI_DEFINE_STATIC_T_V_(R, name, __VA_ARGS__)) /* not ##__VA_ARGS__ !*/

// how to get current function result type easily?
#define JMI_DEFINE_T_V_(R, NAME, ARG_T, ARG_T_V, ARG_V) \
    R NAME ARG_T_V { \
        constexpr const char* kName = __func__; \
        struct MT : MethodTag { static const char* name() {return kName;}}; \
        return call<R, MT> ARG_V; \
    }

#define JMI_DEFINE_T_V_CONST_(R, NAME, ARG_T, ARG_T_V, ARG_V) \
    R NAME ARG_T_V const { \
        constexpr const char* kName = __func__; \
        struct MT : MethodTag { static const char* name() {return kName;}}; \
        return call<R, MT> ARG_V; \
    }

#define JMI_DEFINE_STATIC_T_V_(R, NAME, ARG_T, ARG_T_V, ARG_V) \
    R NAME ARG_T_V { \
        constexpr const char* kName = __func__; \
        struct MT : MethodTag { static const char* name() {return kName;}}; \
        return callStatic<R, MT> ARG_V; \
    }

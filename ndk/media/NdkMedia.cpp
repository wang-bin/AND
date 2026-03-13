/*
 * AND: Android Native Dev in Modern C++ based on JMI
 * Copyright (C) 2026 Wang Bin - wbsecg1@gmail.com
 * https://github.com/wang-bin/AND
 * https://github.com/wang-bin/JMI
 * MIT License
 */

#include "NdkMedia.h"
#include <dlfcn.h>

NDKMEDIA_NS_BEGIN

static bool sEmulated = false;

void* mediandk_so()
{
    if (sEmulated)
        return nullptr;
    static void* dso = dlopen("libmediandk.so", RTLD_LAZY | RTLD_LOCAL);
    return dso;
}

NDKMEDIA_NS_END

void mediandk_set_emulated(bool value)
{
    NDKMEDIA_NS::sEmulated = value;
}

bool mediandk_is_emulated()
{
    return !NDKMEDIA_NS::mediandk_so();
}

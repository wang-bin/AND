/*
 * AND: Android Native Dev in Modern C++ based on JMI
 * Copyright (C) 2026 Wang Bin - wbsecg1@gmail.com
 * https://github.com/wang-bin/AND
 * https://github.com/wang-bin/JMI
 * MIT License
 */

#pragma once

#include "NdkMediaError.hpp"

NDKMEDIA_NS_BEGIN

void* mediandk_so();

NDKMEDIA_NS_END

void mediandk_set_emulated(bool value);
bool mediandk_is_emulated();

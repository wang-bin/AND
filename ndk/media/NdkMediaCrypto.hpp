/*
 * AND: Android Native Dev in Modern C++ based on JMI
 * Copyright (C) 2018-2019 Wang Bin - wbsecg1@gmail.com
 * https://github.com/wang-bin/AND
 * https://github.com/wang-bin/JMI
 * MIT License
 */
#pragma once
#include "NdkMediaError.hpp"
#include <stdint.h>

NDKMEDIA_NS_BEGIN

struct AMediaCrypto;
typedef struct AMediaCrypto AMediaCrypto;

typedef uint8_t AMediaUUID[16];

// api 21 
bool AMediaCrypto_isCryptoSchemeSupported(const AMediaUUID uuid);
bool AMediaCrypto_requiresSecureDecoderComponent(const char *mime);
AMediaCrypto* AMediaCrypto_new(const AMediaUUID uuid, const void *initData, size_t initDataSize);
void AMediaCrypto_delete(AMediaCrypto* crypto);
NDKMEDIA_NS_END
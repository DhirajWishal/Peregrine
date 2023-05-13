// Copyright 2023 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <Arduino.h>

/**
 * @brief No-op function.
 * This function does not do anything and will be optimized out.
 */
inline void NoOp() {}

#if defined(PEREGRINE_DEBUG) || defined(PEREGRINE_PRODUCTION_TEST)
#define PEREGRINE_SETUP_LOGGING(bound) Serial.begin(bound)
#define PEREGRINE_PRINT(...) Serial.print(__VA_ARGS__)
#define PEREGRINE_PRINTLN(...) Serial.println(__VA_ARGS__)
#define PEREGRINE_PRINTF(...) Serial.printf(__VA_ARGS__)

#else
#define PEREGRINE_SETUP_LOGGING(bound) NoOp()
#define PEREGRINE_PRINT(...) NoOp()
#define PEREGRINE_PRINTLN(...) NoOp()
#define PEREGRINE_PRINTF(...) NoOp()

#endif
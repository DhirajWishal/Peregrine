// Copyright 2023 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

constexpr auto g_ThrottleInputMinimum = 0;
constexpr auto g_ThrottleInputMaximum = 1000;

constexpr auto g_RotationalInputMinimum = -90;
constexpr auto g_RotationalInputMaximum = 90;

constexpr auto g_SensorInputMinimum = g_RotationalInputMinimum;
constexpr auto g_SensorInputMaximum = g_RotationalInputMaximum;

constexpr auto g_MinimumRotationalSpeed = 0;   // degrees per second.
constexpr auto g_MaximumRotationalSpeed = 180; // degrees per second.

constexpr auto g_PIDOutputMinimum = 0;
constexpr auto g_PIDOutputMaximum = 180;
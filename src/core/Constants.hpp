// Copyright 2023 Nexonous
// SPDX-License-Identifier: Apache-2.0

#pragma once

// The drone is controlled using inputs and the rotors and servos are controlled using outputs.
// Input limits should somewhat match the outputs. This makes processing simpler. Because at the end of the day, the outputs will be 0 - 180.
//
// Thrust has a higher range, from 0 to 1000.
// Pitch, roll and yaw have a comparatively restricted 90 degrees.
// The pitch, which involves the wing servos, can only travel 45 degrees on each mode. This means the controls can move 90 degrees maximum.
// The roll, is a little different as on hover mode it could be mapped to the thrust value. But on cruise mode, the drone will use the wing servos
// to control the drone. But as with the pitch, it could only move 45 degrees. This is why this value is also restricted to a maximum of 90 degrees.
// The yaw is the same as roll but is inverted; on hover mode, this uses the wing servos. This means it only has a 45 degree movement range. This is
// why this too is restricted to 90 degrees.

constexpr auto g_ThrottleInputMinimum = 0;
constexpr auto g_ThrottleInputMiddle = 500;
constexpr auto g_ThrottleInputMaximum = 1000;

constexpr auto g_PitchInputMinimum = -45;
constexpr auto g_PitchInputMiddle = 0;
constexpr auto g_PitchInputMaximum = 45;

constexpr auto g_RollInputMinimum = g_PitchInputMinimum;
constexpr auto g_RollInputMiddle = g_PitchInputMiddle;
constexpr auto g_RollInputMaximum = g_PitchInputMaximum;

constexpr auto g_YawInputMinimum = g_RollInputMinimum;
constexpr auto g_YawInputMiddle = g_RollInputMiddle;
constexpr auto g_YawInputMaximum = g_RollInputMaximum;

constexpr auto g_ServoOutputMinimum = 0;
constexpr auto g_ServoOutputMaximum = 180;

constexpr auto g_SensorInputMinimum = -90;
constexpr auto g_SensorInputMiddle = 0;
constexpr auto g_SensorInputMaximum = 90;

constexpr auto g_PIDOutputMinimum = g_SensorInputMinimum;
constexpr auto g_PIDOutputMiddle = g_SensorInputMiddle;
constexpr auto g_PIDOutputMaximum = g_SensorInputMaximum;

constexpr auto g_WingServoOffsetHover = 45;
constexpr auto g_WingServoOffsetCruise = 135;

constexpr auto g_ElevatorOffset = 90;
constexpr auto g_RudderOffset = 90;
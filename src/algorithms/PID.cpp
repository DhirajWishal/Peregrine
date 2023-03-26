// Copyright 2023 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "PID.hpp"

#include "core/Common.hpp"
#include "core/Constants.hpp"

#include <Arduino.h>

constexpr auto g_RangeMinimum = -1000000.0f;
constexpr auto g_RangeMaximum = 1000000.0f;

PID::PID(float kp, float ki, float kd)
	: m_PreviousTime(millis()), m_kP(kp), m_kI(ki), m_kD(kd)
{
}

float PID::calculate(float current, float expected)
{
	const auto currentTime = millis();
	const auto deltaTime = currentTime - m_PreviousTime;

	const auto error = expected - current;
	const auto derivative = m_kD * (current - m_PreviousValue);

	m_Integral += error * deltaTime;

	m_PreviousValue = current;
	m_PreviousTime = currentTime;

	const auto output = clamp((m_kP * error) + (m_kI * m_Integral) + derivative, g_RangeMinimum, g_RangeMaximum);
	return map(output, g_RangeMinimum, g_RangeMaximum, g_PIDOutputMinimum, g_PIDOutputMaximum);
}

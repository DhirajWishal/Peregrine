// Copyright 2023 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "PID.hpp"

#include "core/Common.hpp"
#include "core/Constants.hpp"

#include <Arduino.h>

PID::PID(float kp, float ki, float kd)
	: m_kP(kp), m_kI(ki), m_kD(kd)
{
}

float PID::calculate(float current, float expected)
{
	// Calcualte the error, derivative and integral.
	const auto error = expected - current;
	const auto derivative = m_kD * (current - m_PreviousValue);
	m_Integral = clamp(m_Integral + (m_kI * error), static_cast<float>(g_PIDOutputMinimum), static_cast<float>(g_PIDOutputMaximum));
	m_PreviousValue = current;

	// Calculate the output and clamp it in between the required ranges.
	const auto output = (m_kP * error) + m_Integral - derivative;

	if (output < g_PIDOutputMinimum)
		return g_PIDOutputMinimum;

	if (output > g_PIDOutputMaximum)
		return g_PIDOutputMaximum;

	return output;
}

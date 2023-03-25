// Copyright 2023 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "PID.hpp"

#include <Arduino.h>

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

	return (m_kP * error) + (m_kI * m_Integral) + derivative;
}

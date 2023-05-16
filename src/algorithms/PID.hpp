// Copyright 2023 Nexonous
// SPDX-License-Identifier: Apache-2.0

#pragma once

/**
 * @brief PID class.
 * PID is used to stabilize each of the 3 rotations (pitch, roll and yaw).
 * This class is intended to be instanced one for each axis.
 */
class PID final
{
public:
	/**
	 * @brief Construct a new PID object.
	 *
	 * @param kp The proportional constant.
	 * @param ki The integral constant.
	 * @param kd The derivative constant.
	 */
	explicit PID(float kp, float ki, float kd);

	/**
	 * @brief Calculate the PID output.
	 *
	 * @param current The current value.
	 * @param expected The expected value.
	 * @return The result.
	 */
	[[nodiscard]] float calculate(float current, float expected);

private:
	float m_kP = 0.0f;
	float m_kI = 0.0f;
	float m_kD = 0.0f;

	float m_PreviousValue = 0.0f;

	float m_Integral = 0.0f;
};
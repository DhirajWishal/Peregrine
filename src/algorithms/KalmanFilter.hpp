// Copyright 2023 Nexonous
// SPDX-License-Identifier: Apache-2.0

#pragma once

/**
 * @brief Kalman filter class.
 * This filter is used to filter out the noisy inputs of the accelerometer and the gyroscope.
 */
class KalmanFilter final
{
public:
	/**
	 * @brief Construct a new Kalman Filter object.
	 */
	KalmanFilter() = default;

	/**
	 * @brief Set the angle.
	 *
	 * @param angle The angle to set.
	 */
	void setAngle(float angle);

	/**
	 * @brief Compute the output angle.
	 *
	 * @param angle The incoming angle.
	 * @param rate The rate.
	 * @param delta The time delta.
	 * @return The output angle.
	 */
	float compute(float angle, float rate, float delta);

	/**
	 * @brief Tune the Kalman filter.
	 *
	 * @param angle The constant angle.
	 * @param bias The constant bias.
	 * @param measure The measurement bias.
	 */
	void tune(float angle, float bias, float measure);

private:
	float m_ErrorMatrix[2][2] = {0};

	float m_ConstantAngle = 0.001f;
	float m_ConstantBias = 0.003f;
	float m_Measure = 0.03f;

	float m_Angle = 0.0f;
	float m_Bias = 0.0f;
	float m_Rate = 0.0f;

	float m_ResetAngle = 0.0f;
	float m_ResetBias = 0.0f;

	bool m_isInitialized = false;
};
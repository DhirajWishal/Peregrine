// Copyright 2023 Nexonous
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "core/System.hpp"
#include "components/MPU6050.hpp"
#include "algorithms/PID.hpp"

/**
 * @brief The PID algorithm uses some constants which can be tuned by the user to stabilize the incoming values.
 * Edit the following constants to tune the PID stabilization (for each control axis).
 */

constexpr auto g_PitchKP = 0.001f;
constexpr auto g_PitchKI = 0.01f;
constexpr auto g_PitchKD = 1.0f;

constexpr auto g_RollKP = 0.001f;
constexpr auto g_RollKI = 0.01f;
constexpr auto g_RollKD = 1.0f;

constexpr auto g_YawKP = 0.001f;
constexpr auto g_YawKI = 0.01f;
constexpr auto g_YawKD = 1.0f;

/**
 * @brief Stabilizer class.
 * This class runs the stabilization algorithm
 */
class Stabilizer final : public System<Stabilizer>
{
public:
	/**
	 * @brief Construct a new Stabilizer object.
	 */
	Stabilizer();

	/**
	 * @brief Initialize the stabilizer.
	 */
	void initialize();

	/**
	 * @brief Update the stabilizer.
	 */
	void update() override;

	float yawValue() { return m_Sensor.getAcceleration().m_Pitch; }

	Vec3 computeOutputs(float thrust, float pitch, float roll, float yaw);

private:
	MPU6050 m_Sensor;

	PID m_PitchStabilizer;
	PID m_RollStabilizer;
	PID m_YawStabilizer;
};
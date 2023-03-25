// Copyright 2023 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "core/System.hpp"
#include "components/MPU6050.hpp"
#include "algorithms/PID.hpp"

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
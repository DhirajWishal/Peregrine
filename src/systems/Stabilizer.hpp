// Copyright 2023 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "core/System.hpp"
#include "components/MPU6050.hpp"

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
	Stabilizer() = default;

	/**
	 * @brief Initialize the stabilizer.
	 */
	void initialize();

	/**
	 * @brief Update the stabilizer.
	 */
	void update() override;

private:
	MPU6050 m_Sensor;
};
// Copyright 2023 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

constexpr auto g_SensorSDA = 18;
constexpr auto g_SensorSCL = 19;

#include <Adafruit_MPU6050.h>

/**
 * @brief MPU6050 driver class.
 * This class sets up the connection to the MPU6050 sensor and contains utility methods to read raw and/ or processed data.
 */
class MPU6050 final
{
public:
	/**
	 * @brief Construct a new MPU6050 object.
	 */
	MPU6050() = default;

	/**
	 * @brief Initialize the sensor.
	 */
	void initialize();

	/**
	 * @brief Read the sensor data.
	 */
	void readData();

private:
	Adafruit_MPU6050 m_Module;
};
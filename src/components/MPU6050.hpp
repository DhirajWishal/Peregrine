// Copyright 2023 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "core/Types.hpp"

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

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

	/**
	 * @brief Get the temperature reading.
	 *
	 * @return The temperature reading in celcius.
	 */
	[[nodiscard]] float getTemperature() const { return m_Temperature.temperature; }

	/**
	 * @brief Get the acceleration data.
	 *
	 * @return The 3 component vector with the values.
	 */
	[[nodiscard]] Vec3 getAcceleration() const { return Vec3(m_Accelerometer.acceleration.x, m_Accelerometer.acceleration.y, m_Accelerometer.acceleration.z); }

	/**
	 * @brief Get the gyroscope data.
	 *
	 * @return The 3 component vector with the values.
	 */
	[[nodiscard]] Vec3 getGyration() const { return Vec3(m_Gyroscope.gyro.x, m_Gyroscope.gyro.y, m_Gyroscope.gyro.z); }

private:
	Adafruit_MPU6050 m_Module;

	sensors_event_t m_Temperature;
	sensors_event_t m_Accelerometer;
	sensors_event_t m_Gyroscope;
};
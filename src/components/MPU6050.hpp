// Copyright 2023 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "core/Types.hpp"
#include "algorithms/KalmanFilter.hpp"

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
	MPU6050();

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
	 * @return The temperature reading in celsius.
	 */
	[[nodiscard]] float getTemperature() const { return m_Temperature; }

	/**
	 * @brief Get the acceleration data.
	 *
	 * @return The 3 component vector with the values in meters per square second.
	 */
	[[nodiscard]] Vec3 getAcceleration() const { return m_Accelerometer; }

	/**
	 * @brief Get the gyroscope data.
	 *
	 * @return The 3 component vector with the values in degrees per second (0 - 180).
	 */
	[[nodiscard]] Vec3 getGyration() const { return m_Gyroscope; }

	/**
	 * @brief Get the Accelerometer Range object.
	 *
	 * @return The range.
	 */
	[[nodiscard]] mpu6050_accel_range_t getAccelerometerRange() { return m_Module.getAccelerometerRange(); }

	/**
	 * @brief Get the Gyroscope Range object.
	 *
	 * @return The range.
	 */
	[[nodiscard]] mpu6050_gyro_range_t getGyroscopeRange() { return m_Module.getGyroRange(); }

private:
	/**
	 * @brief Process the accelerometer data.
	 *
	 * @param event The sensor event.
	 */
	void processAccelerometerData(sensors_event_t event);

	/**
	 * @brief Process the gyroscopic data.
	 *
	 * @param event The sensor event.
	 */
	void processGyroscopicData(sensors_event_t event);

private:
	Adafruit_MPU6050 m_Module;

	KalmanFilter m_PitchFilter;
	KalmanFilter m_RollFilter;

	Vec3 m_Accelerometer;
	Vec3 m_Gyroscope;
	float m_Temperature;

	unsigned long m_PreviousTime = 0;

	float m_ComplementaryAngleX = 0.0f;
	float m_ComplementaryAngleY = 0.0f;
};
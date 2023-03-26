// Copyright 2023 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "MPU6050.hpp"

#include "core/Constants.hpp"

#include <Arduino.h>

constexpr auto g_ConvertionConstant = 57.2957795f;

void MPU6050::initialize()
{
	Serial.println("Initializing the MPU6050 sensor.");

	// Initialize the module.
	if (!m_Module.begin())
	{
		Serial.println("Failed to find MPU6050 chip!");
		return;
	}

	// Setup the initial configuration.
	m_Module.setAccelerometerRange(MPU6050_RANGE_8_G);
	m_Module.setGyroRange(MPU6050_RANGE_500_DEG);
	m_Module.setFilterBandwidth(MPU6050_BAND_21_HZ);

	Serial.println("MPU6050 sensor is initialized.");
}

void MPU6050::readData()
{
	// Get the data from the sensor.
	sensors_event_t accelerometer;
	sensors_event_t gyroscope;
	sensors_event_t temperature;
	m_Module.getEvent(&accelerometer, &gyroscope, &temperature);

	// Process the data.
	processAccelerometerData(accelerometer);
	processGyroscopicData(gyroscope);
	m_Temperature = temperature.temperature;
}

void MPU6050::processAccelerometerData(sensors_event_t event)
{
	// Setup the rotation ranges.
	float rangeMinimum = -8.0f;
	float rangeMaximum = 8.0f;

	switch (m_Module.getAccelerometerRange())
	{
	case MPU6050_RANGE_2_G:
		rangeMinimum = -2.0f;
		rangeMaximum = 2.0f;
		break;

	case MPU6050_RANGE_4_G:
		rangeMinimum = -4.0f;
		rangeMaximum = 4.0f;
		break;

	case MPU6050_RANGE_8_G:
		rangeMinimum = -8.0f;
		rangeMaximum = 8.0f;
		break;

	case MPU6050_RANGE_16_G:
		rangeMinimum = -16.0f;
		rangeMaximum = 16.0f;
		break;

	default:
		break;
	}

	// Convert them to the required outputs.
	m_Accelerometer.m_X = map(event.acceleration.x, rangeMinimum, rangeMaximum, g_RotationalMinimum, g_RotationalMaximum);
	m_Accelerometer.m_Y = map(event.acceleration.y, rangeMinimum, rangeMaximum, g_RotationalMinimum, g_RotationalMaximum);
	m_Accelerometer.m_Z = map(event.acceleration.z, rangeMinimum, rangeMaximum, g_RotationalMinimum, g_RotationalMaximum);
}

void MPU6050::processGyroscopicData(sensors_event_t event)
{
	// Convert from rad/s to deg/s
	event.gyro.x *= g_ConvertionConstant;
	event.gyro.y *= g_ConvertionConstant;
	event.gyro.z *= g_ConvertionConstant;

	// Setup the rotation ranges.
	float inputRateMinimum = -500.0f;
	float inputRateMaximum = 500.0f;

	switch (m_Module.getGyroRange())
	{
	case MPU6050_RANGE_250_DEG:
		inputRateMinimum = -250.0f;
		inputRateMaximum = 250.0f;
		break;

	case MPU6050_RANGE_500_DEG:
		inputRateMinimum = -500.0f;
		inputRateMaximum = 500.0f;
		break;

	case MPU6050_RANGE_1000_DEG:
		inputRateMinimum = -1000.0f;
		inputRateMaximum = 1000.0f;
		break;

	case MPU6050_RANGE_2000_DEG:
		inputRateMinimum = -2000.0f;
		inputRateMaximum = 2000.0f;
		break;

	default:
		break;
	}

	// Convert them to the required outputs.
	m_Gyroscope.m_Pitch = map(event.gyro.x, inputRateMinimum, inputRateMaximum, g_MinimumRotationalSpeed, g_MaximumRotationalSpeed);
	m_Gyroscope.m_Yaw = map(event.gyro.y, inputRateMinimum, inputRateMaximum, g_MinimumRotationalSpeed, g_MaximumRotationalSpeed);
	m_Gyroscope.m_Roll = map(event.gyro.z, inputRateMinimum, inputRateMaximum, g_MinimumRotationalSpeed, g_MaximumRotationalSpeed);
}

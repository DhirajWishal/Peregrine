// Copyright 2023 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "MPU6050.hpp"

#include <Arduino.h>

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
	m_Module.getEvent(&m_Accelerometer, &m_Gyroscope, &m_Temperature);
}

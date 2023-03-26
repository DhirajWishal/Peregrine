// Copyright 2023 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "MPU6050.hpp"

#include "core/Constants.hpp"

#include <Arduino.h>

// 1 Rad/s = 57.2957795 deg/s
constexpr auto g_RadiansToDegrees = 57.2957795f;

MPU6050::MPU6050()
	: m_PreviousTime(micros())
{
}

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
	const auto currentTime = micros();
	m_DeltaTime = currentTime - m_PreviousTime;
	m_PreviousTime = currentTime;

	// Get the data from the sensor.
	sensors_event_t accelerometer;
	sensors_event_t gyroscope;
	sensors_event_t temperature;
	m_Module.getEvent(&accelerometer, &gyroscope, &temperature);

	// Process the data.
	processGyroscopicData(gyroscope);
	processAccelerometerData(accelerometer);
	m_Temperature = temperature.temperature;
}

void MPU6050::processAccelerometerData(sensors_event_t event)
{
	const auto pitch = atan2(event.acceleration.y, event.acceleration.z) * g_RadiansToDegrees;
	const auto roll = atan2(-event.acceleration.x, sqrt((event.acceleration.y * event.acceleration.y) + (event.acceleration.z * event.acceleration.z))) * g_RadiansToDegrees;
	m_Accelerometer.m_Y = event.acceleration.y;

	// This fixes the transition problem when the accelerometer angle jumps between -180 and 180 degrees
	if ((pitch < -90 && m_Accelerometer.m_Pitch > 90) || (pitch > 90 && m_Accelerometer.m_Pitch < -90))
	{
		m_PitchFilter.setAngle(pitch);

		m_ComplementaryAngleY = pitch;
		m_Accelerometer.m_Pitch = pitch;
		m_Gyroscope.m_Y = pitch;
	}
	else
	{
		m_Accelerometer.m_Pitch = m_PitchFilter.compute(pitch, m_Gyroscope.m_Pitch, m_DeltaTime); // Calculate the angle using a Kalman filter
	}

	if (abs(m_Accelerometer.m_Roll) > 90)
		m_Gyroscope.m_Roll = -m_Gyroscope.m_Roll; // Invert rate, so it fits the restriced accelerometer reading

	m_Accelerometer.m_Roll = m_RollFilter.compute(roll, m_Gyroscope.m_Roll, m_DeltaTime); // Calculate the angle using a Kalman filter

	const auto gyroXrate = m_Gyroscope.m_X;
	const auto gyroYrate = m_Gyroscope.m_Y;

	m_Gyroscope.m_X += m_Gyroscope.m_X * m_DeltaTime; // Calculate gyro angle without any filter
	m_Gyroscope.m_Y += m_Gyroscope.m_Y * m_DeltaTime;

	m_ComplementaryAngleX = 0.93 * (m_ComplementaryAngleX + gyroXrate * m_DeltaTime) + 0.07 * roll; // Calculate the angle using a Complimentary filter
	m_ComplementaryAngleY = 0.93 * (m_ComplementaryAngleY + gyroYrate * m_DeltaTime) + 0.07 * pitch;

	// Reset the gyro angle when it has drifted too much
	if (m_Gyroscope.m_X < -180 || m_Gyroscope.m_X > 180)
		m_Gyroscope.m_X = m_Accelerometer.m_Pitch;

	if (m_Gyroscope.m_Y < -180 || m_Gyroscope.m_Y > 180)
		m_Gyroscope.m_Y = m_Accelerometer.m_Roll;
}

void MPU6050::processGyroscopicData(sensors_event_t event)
{
	// Convert from rad/s to deg/s
	m_Gyroscope.m_X = event.gyro.x * g_RadiansToDegrees;
	m_Gyroscope.m_Y = event.gyro.y * g_RadiansToDegrees;
	m_Gyroscope.m_Z = event.gyro.z * g_RadiansToDegrees;
}

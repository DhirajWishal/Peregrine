// Copyright 2023 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "Stabilizer.hpp"

#include "core/Constants.hpp"

Stabilizer::Stabilizer()
	: m_PitchStabilizer(0.5f, 0.5f, 0.5f), m_RollStabilizer(0.5f, 0.5f, 0.5f), m_YawStabilizer(0.5f, 0.5f, 0.5f)
{
}

void Stabilizer::initialize()
{
	Serial.println("Initializing the Stabilizer.");

	// Initialize the sensor.
	m_Sensor.initialize();

	Serial.println("Stabilizer is initialized.");
}

void Stabilizer::update()
{
	m_Sensor.readData();
}

Vec3 Stabilizer::computeOutputs(float thrust, float pitch, float roll, float yaw)
{
	const auto acceleration = m_Sensor.getAcceleration();
	const auto gyration = m_Sensor.getGyration();

	const auto currentPitch = map(acceleration.m_Pitch * 100, -1000, 1000, 0, 180);
	const auto currentYaw = map(acceleration.m_Yaw * 100, -1000, 1000, 0, 180);
	const auto currentRoll = map(acceleration.m_Roll * 100, -1000, 1000, 0, 180);

	const auto expectedPitch = map(pitch, g_RotationalMaximum, g_RotationalMaximum, 0, 180);
	const auto expectedYaw = map(yaw, g_RotationalMaximum, g_RotationalMaximum, 0, 180);
	const auto expectedRoll = map(roll, g_RotationalMaximum, g_RotationalMaximum, 0, 180);

	const auto outputPitch = m_PitchStabilizer.calculate(currentPitch, expectedPitch);
	const auto outputYaw = m_YawStabilizer.calculate(currentYaw, expectedYaw);
	const auto outputRoll = m_RollStabilizer.calculate(currentRoll, expectedRoll);

	return Vec3(outputPitch, outputYaw, outputRoll);
}

// Copyright 2023 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "Stabilizer.hpp"

template <class Type>
inline Type clamp(Type input, Type min, Type max)
{
	if (input < min)
		return min;
	if (input > max)
		return max;

	return input;
}

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
	// These expected values are in degrees per second.
	const auto expectedPitch = map(pitch, g_RotationalMaximum, g_RotationalMaximum, g_MinimumRotationalSpeed, g_MaximumRotationalSpeed);
	const auto expectedYaw = map(yaw, g_RotationalMaximum, g_RotationalMaximum, g_MinimumRotationalSpeed, g_MaximumRotationalSpeed);
	const auto expectedRoll = map(roll, g_RotationalMaximum, g_RotationalMaximum, g_MinimumRotationalSpeed, g_MaximumRotationalSpeed);

	const auto acceleration = m_Sensor.getAcceleration();
	const auto rotationRate = m_Sensor.getGyration();

	// These current values are in degrees per second.
	const auto currentPitch = rotationRate.m_Pitch;
	const auto currentYaw = rotationRate.m_Yaw;
	const auto currentRoll = rotationRate.m_Roll;

	Serial.print(" | Pitch: ");
	Serial.print(currentPitch);
	Serial.print(" | Roll: ");
	Serial.print(currentRoll);
	Serial.print(" | Yaw: ");
	Serial.print(currentYaw);
	Serial.println();

	const auto outputPitch = m_PitchStabilizer.calculate(currentPitch, expectedPitch);
	const auto outputYaw = m_YawStabilizer.calculate(currentYaw, expectedYaw);
	const auto outputRoll = m_RollStabilizer.calculate(currentRoll, expectedRoll);

	return Vec3(outputPitch, outputYaw, outputRoll);
}

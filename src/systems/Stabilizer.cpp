// Copyright 2023 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "Stabilizer.hpp"

#include "core/Constants.hpp"

constexpr auto g_PitchKP = 0.001f;
constexpr auto g_PitchKI = 0.01f;
constexpr auto g_PitchKD = 1.0f;

constexpr auto g_RollKP = 0.001f;
constexpr auto g_RollKI = 0.01f;
constexpr auto g_RollKD = 1.0f;

constexpr auto g_YawKP = 0.001f;
constexpr auto g_YawKI = 0.01f;
constexpr auto g_YawKD = 1.0f;

Stabilizer::Stabilizer()
	: m_PitchStabilizer(g_PitchKP, g_PitchKI, g_PitchKD), m_RollStabilizer(g_RollKP, g_RollKI, g_RollKD), m_YawStabilizer(g_YawKP, g_YawKI, g_YawKD)
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
	const auto angles = m_Sensor.getAcceleration();
	// const auto rotationRate = m_Sensor.getGyration();

	const auto outputPitch = m_PitchStabilizer.calculate(angles.m_Pitch, pitch);
	const auto outputYaw = m_YawStabilizer.calculate(angles.m_Yaw, yaw);
	const auto outputRoll = m_RollStabilizer.calculate(angles.m_Roll, roll);

	return Vec3(outputPitch, outputYaw, outputRoll);
}

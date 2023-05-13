// Copyright 2023 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "Stabilizer.hpp"

#include "core/Constants.hpp"
#include "core/Logging.hpp"

#include "benchmark/ScopedTimer.hpp"

Stabilizer::Stabilizer()
	: m_PitchStabilizer(g_PitchKP, g_PitchKI, g_PitchKD), m_RollStabilizer(g_RollKP, g_RollKI, g_RollKD), m_YawStabilizer(g_YawKP, g_YawKI, g_YawKD)
{
}

void Stabilizer::initialize()
{
	PEREGRINE_PRINTLN("Initializing the Stabilizer.");

	// Initialize the sensor.
	m_Sensor.initialize();

	PEREGRINE_PRINTLN("Stabilizer is initialized.");
}

void Stabilizer::update()
{
	m_Sensor.readData();
}

Vec3 Stabilizer::computeOutputs(float thrust, float pitch, float roll, float yaw)
{
	const auto angles = m_Sensor.getAcceleration();
	const auto outputPitch = m_PitchStabilizer.calculate(angles.m_Pitch, pitch);
	const auto outputRoll = m_RollStabilizer.calculate(angles.m_Roll, roll);

	// Since we don't have a way to calculate yaw properly using the sensor (unless we have a magnetometer), use the gyration.
	const auto rotationRate = m_Sensor.getGyration();
	const auto outputYaw = m_YawStabilizer.calculate(rotationRate.m_Yaw, yaw);

	// BEGINNING OF TEST ZONE!
	{
		PEREGRINE_SETUP_SCOPED_TIMER();
		m_NeuralNetwork.run({thrust, pitch, roll, yaw, angles.m_Pitch, angles.m_Roll, angles.m_Yaw, rotationRate.m_Pitch, rotationRate.m_Roll, rotationRate.m_Yaw});

		PEREGRINE_PRINTF("NN output LWR: %f\n", m_NeuralNetwork.getOutput(0));
		PEREGRINE_PRINTF("NN output RWR: %f\n", m_NeuralNetwork.getOutput(1));
		PEREGRINE_PRINTF("NN output LWS: %f\n", m_NeuralNetwork.getOutput(2));
		PEREGRINE_PRINTF("NN output RWS: %f\n", m_NeuralNetwork.getOutput(3));
		PEREGRINE_PRINTF("NN output TES: %f\n", m_NeuralNetwork.getOutput(4));
		PEREGRINE_PRINTF("NN output TRS: %f\n", m_NeuralNetwork.getOutput(5));

		// m_NeuralNetwork.train();
	}
	// END OF TEST ZONE!

	return Vec3(outputPitch, outputYaw, outputRoll);
}

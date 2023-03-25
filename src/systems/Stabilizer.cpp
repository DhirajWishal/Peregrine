// Copyright 2023 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "Stabilizer.hpp"

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

	// Get the readings.
	const auto a = m_Sensor.getAcceleration();
	const auto g = m_Sensor.getGyration();
	const auto t = m_Sensor.getTemperature();

	/* Print out the values */
	Serial.print("Acceleration X: ");
	Serial.print(a.m_X);
	Serial.print(", Y: ");
	Serial.print(a.m_Y);
	Serial.print(", Z: ");
	Serial.print(a.m_Z);
	Serial.println(" m/s^2");

	Serial.print("Rotation X: ");
	Serial.print(g.m_X);
	Serial.print(", Y: ");
	Serial.print(g.m_Y);
	Serial.print(", Z: ");
	Serial.print(g.m_Z);
	Serial.println(" rad/s");

	Serial.print("Temperature: ");
	Serial.print(t);
	Serial.println(" degC");
}

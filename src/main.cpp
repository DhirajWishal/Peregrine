// Copyright 2023 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "systems/OutputSystem.hpp"
#include "systems/Stabilizer.hpp"

void setup()
{
	Serial.begin(9600);
	Serial.println("Welcome to Peregrine!");
	Serial.println("Initializing the controller.");

	// Initialize the output system.
	OutputSystem::Instance().initialize();

	// Setup motors
	// Setup servos
	// Setup stabilizer
	// Setup coms

	Serial.println("The controller initialized. Entering the main loop.");
}

void loop()
{
	// Upate coms

	// Update the stabilization.
	Stabilizer::Instance().update();

	// Update the output system.
	OutputSystem::Instance().update();
}
// Copyright 2023 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "systems/output/OutputSystem.hpp"

void setup()
{
	Serial.begin(9600);
	Serial.println("Welcome to Peregrine!");
	Serial.println("Initializing the controller.");

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
	// Update stabilizer
	// Update outputs
}
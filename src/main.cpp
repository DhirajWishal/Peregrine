// Copyright 2023 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "systems/OutputSystem.hpp"
#include "systems/Stabilizer.hpp"
#include "systems/InputSystem.hpp"

#include "components/DefaultDataLink.hpp"
DefaultDataLink g_DefaultDataLink;

void setup()
{
	Serial.begin(115200);
	Serial.println("Welcome to Peregrine!");
	Serial.println("Initializing the controller.");

	// Initialize the stabilizer.
	Stabilizer::Instance().initialize();

	// Initialize the output system.
	OutputSystem::Instance().initialize();

	// Initialize the input sytem.
	InputSystem::Instance().initialize(&g_DefaultDataLink);

	Serial.println("The controller initialized. Entering the main loop.");
}

void loop()
{
	// Update the input system.
	InputSystem::Instance().update();

	// Update the stabilization.
	Stabilizer::Instance().update();

	// Update the output system.
	OutputSystem::Instance().update();
}
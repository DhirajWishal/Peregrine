// Copyright 2023 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "systems/OutputSystem.hpp"
#include "systems/Stabilizer.hpp"
#include "systems/InputSystem.hpp"
#include "core/Configuration.hpp"

#if defined(PEREGRINE_DATA_LINK_FS_I6)
#include "components/FSi6DataLink.hpp"
FSi6DataLink g_CurrentDataLink;

#elif defined(PEREGRINE_DATA_LINK_NRF24L01)
#include "components/DefaultDataLink.hpp"
DefaultDataLink g_CurrentDataLink;

#else
#include "components/DefaultDataLink.hpp"
DefaultDataLink g_CurrentDataLink;

#endif

#include "core/Logging.hpp"

void setup()
{
	PEREGRINE_SETUP_LOGGING(115200);
	PEREGRINE_PRINTLN("Welcome to Peregrine!");
	PEREGRINE_PRINTLN("Initializing the controller.");

	// Initialize the stabilizer.
	Stabilizer::Instance().initialize();

	// Initialize the output system.
	OutputSystem::Instance().initialize();

	// Initialize the input system.
	InputSystem::Instance().initialize(&g_CurrentDataLink);

	PEREGRINE_PRINTLN("The controller initialized. Entering the main loop.");
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
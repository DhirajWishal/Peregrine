// Copyright 2023 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "InputSystem.hpp"

void InputSystem::initialize(IDataLink *pDataLink)
{
	Serial.println("Initializing the input system.");
	m_pDataLink = pDataLink;

	// Validate the data link pointer.
	if (!m_pDataLink)
	{
		Serial.println("The data link pointer is invalid!");
		return;
	}

	// Initialize the data link.
	m_pDataLink->onInitialize();

	Serial.println("The input system is initialized.");
}

void InputSystem::update()
{
	m_pDataLink->onUpdate();
}

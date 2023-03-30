// Copyright 2023 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "InputSystem.hpp"

#include "core/Logging.hpp"

void InputSystem::initialize(IDataLink *pDataLink)
{
	PEREGRINE_PRINTLN("Initializing the input system.");
	m_pDataLink = pDataLink;

#ifdef PEREGRINE_DEBUG
	// Validate the data link pointer.
	if (!m_pDataLink)
	{
		PEREGRINE_PRINTLN("The data link pointer is invalid!");
		return;
	}

#endif

	// Initialize the data link.
	m_pDataLink->onInitialize();

	PEREGRINE_PRINTLN("The input system is initialized.");
}

void InputSystem::update()
{
#ifdef PEREGRINE_DEBUG
	// Validate the data link pointer.
	if (!m_pDataLink)
	{
		PEREGRINE_PRINTLN("The data link pointer is invalid!");
		return;
	}

#endif

	m_pDataLink->onUpdate();
}

// Copyright 2023 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <stdint.h>

/**
 * @brief Fly mode enum.
 * This defines all the possible fly modes of the controller.
 */
enum class FlyMode : uint8_t
{
	// Hover mode is when the drone starts from the ground to take off, or when is about to land (motors facing up).
	Hover,

	// Cruise mode is when the drone is flying (motors facing front).
	Cruise
};

// This variable stores the current fly mode.
extern FlyMode g_CurrentFlyMode;

// This variable stores the required fly mode.
// A change in the this variable will result in a transition (Hover -> Cruise or Cruise -> Hover).
extern FlyMode g_RequiredFlyMode;

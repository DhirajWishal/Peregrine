// Copyright 2023 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <Arduino.h>

/**
 * @brief Main system class.
 * This is the base class for all the systems and systems are intended to be singletons.
 *
 * @tparam Derived The derived type.
 */
template <class Derived>
class System
{
protected:
	/**
	 * @brief Construct a new System object.
	 */
	System() = default;

	/**
	 * @brief Destroy the System object.
	 */
	virtual ~System() = default;

public:
	/**
	 * @brief Get the system instance.
	 *
	 * @return The class reference.
	 */
	static Derived &Instance()
	{
		static Derived instance;
		return instance;
	}

	/**
	 * @brief Update pure virtual method.
	 * This method is called by the loop function and the derived class must use this method to update itself.
	 */
	virtual void update() = 0;
};

inline float map(float x, float in_min, float in_max, float out_min, float out_max)
{
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
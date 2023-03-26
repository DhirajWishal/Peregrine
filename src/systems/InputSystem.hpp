// Copyright 2023 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "core/System.hpp"
#include "core/IDataLink.hpp"

/**
 * @brief Input system class.
 * This class contains information about the inputs given by either an engine, or an RF signal.
 */
class InputSystem final : public System<InputSystem>
{
public:
	/**
	 * @brief Construct a new Input System object.
	 */
	InputSystem() = default;

	/**
	 * @brief Initialize the input sytem.
	 *
	 * @param pDataLink The data link pointer.
	 */
	void initialize(IDataLink *pDataLink);

	/**
	 * @brief Update the input system.
	 */
	void update() override;

	/**
	 * @brief Get thrust method.
	 * Return the required thrust.
	 *
	 * @return The trust value (0 - 1000).
	 */
	[[nodiscard]] float getThrust() { return m_pDataLink->onGetThrust(); }

	/**
	 * @brief Get pitch method.
	 * Required pitch value.
	 *
	 * @return The pitch value (-90 - 90).
	 */
	[[nodiscard]] float getPitch() { return m_pDataLink->onGetPitch(); }

	/**
	 * @brief Get roll method.
	 * Required roll value.
	 *
	 * @return The roll value (-90 - 90).
	 */
	[[nodiscard]] float getRoll() { return m_pDataLink->onGetRoll(); }

	/**
	 * @brief Get yaw method.
	 * Return the required yaw value.
	 *
	 * @return The yaw value (-90 - 90).
	 */
	[[nodiscard]] float getYaw() { return m_pDataLink->onGetYaw(); }

private:
	IDataLink *m_pDataLink = nullptr;
};
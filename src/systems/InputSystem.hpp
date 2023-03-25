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

private:
	IDataLink *m_pDataLink = nullptr;
};
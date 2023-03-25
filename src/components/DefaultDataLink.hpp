// Copyright 2023 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "core/IDataLink.hpp"

/**
 * @brief Default data link class.
 * This class is the default data link and is used for debugging purposes.
 */
class DefaultDataLink final : public IDataLink
{
public:
	/**
	 * @brief Construct a new Default Data Link object.
	 */
	DefaultDataLink() = default;

	/**
	 * @brief On initialize method.
	 * This metod is intended to be used to initialize the data link.
	 */
	void onInitialize() override;

	/**
	 * @brief On update method.
	 * This method is intended to be used to update the data link and to poll the latest information.
	 */
	void onUpdate() override;
};
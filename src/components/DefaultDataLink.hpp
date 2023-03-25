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

	/**
	 * @brief On get thrust method.
	 * Return the required thrust.
	 *
	 * @return The trust value (0 - 1000).
	 */
	[[nodiscard]] float onGetThrust() override { return 100.0f; }

	/**
	 * @brief On get pitch method.
	 * Required pitch value.
	 *
	 * @return The pitch value (0 - 100 - 200).
	 */
	[[nodiscard]] float onGetPitch() override { return 100.0f; }

	/**
	 * @brief On get roll method.
	 * Required roll value.
	 *
	 * @return The roll value (0 - 100 - 200).
	 */
	[[nodiscard]] float onGetRoll() override { return 100.0f; }

	/**
	 * @brief On get yaw method.
	 * Return the required yaw value.
	 *
	 * @return The yaw value (0 - 100 - 200).
	 */
	[[nodiscard]] float onGetYaw() override { return 100.0f; }
};
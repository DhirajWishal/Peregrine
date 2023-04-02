// Copyright 2023 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "core/System.hpp"

// Set your WiFi SSID here.
constexpr auto g_SSID = "SSID";

// Set your WiFi password here.
constexpr auto g_Password = "password";

/**
 * @brief WiFi system class.
 * This class is used to communicate with pre-defined WiFis for various purposes. Mainly this is used to communicate with the desktop application to configure the drone.
 */
class WiFiSystem final : public System<WiFiSystem>
{
public:
	/**
	 * @brief Construct a new Wi Fi System object.
	 */
	WiFiSystem() = default;

	/**
	 * @brief Initialize the WiFi system.
	 */
	void initialize();

	/**
	 * @brief Update the WiFi system.
	 */
	void update() override;

private:
	/**
	 * @brief Check if a WiFi with the given SSID exists.
	 *
	 * @return true If the required WiFi exists (after scanning).
	 * @return false If the required WiFi does not exist (after scanning).
	 */
	[[nodiscard]] bool exists() const;
};
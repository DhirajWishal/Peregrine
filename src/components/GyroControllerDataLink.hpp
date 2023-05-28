// Copyright 2023 Nexonous
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "core/Types.hpp"
#include "core/IDataLink.hpp"

#include <nRF24L01.h>
#include <RF24.h>

constexpr auto g_ChipEnablePin = 2;
constexpr auto g_ChipSelectNotPin = 15;
constexpr byte g_DefaultAddress[6] = "GyroC";

/**
 * @brief GyroController module class.
 * This class can be used to communicate with the GyroController.
 */
class GyroControllerDataLink final : public IDataLink
{
public:
	/**
	 * @brief Construct a new GyroController data link object.
	 */
	GyroControllerDataLink();

	/**
	 * @brief On initialize method.
	 * This method is intended to be used to initialize the data link.
	 */
	void onInitialize() override;

	/**
	 * @brief On update method.
	 * This method is intended to be used to update the data link and to poll the latest information.
	 */
	void onUpdate() override;

	/**
	 * @brief On get thrust pure virtual method.
	 * When this method is called the data link should return the required thrust.
	 *
	 * @return The thrust value.
	 */
	[[nodiscard]] float onGetThrust() { return m_ThrottleValue; }

	/**
	 * @brief On get pitch pure virtual method.
	 * When this method is called the data link should return the required pitch value.
	 *
	 * @return The pitch value.
	 */
	[[nodiscard]] float onGetPitch() { return m_Payload.m_Pitch; }

	/**
	 * @brief On get roll pure virtual method.
	 * When this method is called the data link should return the required roll value.
	 *
	 * @return The roll value.
	 */
	[[nodiscard]] float onGetRoll() { return m_Payload.m_Roll; }

	/**
	 * @brief On get yaw pure virtual method.
	 * When this method is called the data link should return the required yaw value.
	 *
	 * @return The yaw value.
	 */
	[[nodiscard]] float onGetYaw() { return m_Payload.m_Roll; }

private:
	RF24 m_Transceiver;
	Vec4 m_Payload;

	float m_ThrottleValue = 0.0f;
};
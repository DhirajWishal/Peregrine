// Copyright 2023 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "core/System.hpp"

#include <Servo.h>

constexpr auto g_LeftMotorPin = 11;
constexpr auto g_RightMotorPin = 10;

constexpr auto g_LeftWingServoPin = 9;
constexpr auto g_RightWingServoPin = 6;
constexpr auto g_ElevatorServoPin = 5;
constexpr auto g_RudderServoPin = 3;

/**
 * @brief Output system class.
 * This class manages all the outputs, including the motors and controlling servos.
 */
class OutputSystem final : public System<OutputSystem>
{
public:
	/**
	 * @brief Construct a new Output System object.
	 */
	OutputSystem() = default;

	/**
	 * @brief Initialize the output system.
	 */
	void initialize();

	/**
	 * @brief Update the output system.
	 */
	void update() override;

private:
	Servo m_LeftWingServo;
	Servo m_RightWingServo;
	Servo m_ElevatorServo;
	Servo m_RudderServo;
};
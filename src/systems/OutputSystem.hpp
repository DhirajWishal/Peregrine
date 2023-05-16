// Copyright 2023 Nexonous
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "core/System.hpp"
#include "core/Types.hpp"

#include <ESP32Servo.h>

constexpr auto g_LeftRotorPin = 32;
constexpr auto g_RightRotorPin = 33;

constexpr auto g_LeftWingServoPin = 25;
constexpr auto g_RightWingServoPin = 26;
constexpr auto g_ElevatorServoPin = 27;
constexpr auto g_RudderServoPin = 14;

/**
 * @brief Output system class.
 * This class manages all the outputs, including the rotors and controlling servos.
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
	/**
	 * @brief Handle the hover mode outputs.
	 * This method gets called when the drone is in hover mode.
	 *
	 * @param thrust The input thrust.
	 * @param outputs The PID outputs.
	 */
	void handleHoverMode(float thrust, Vec3 outputs);

	/**
	 * @brief Handle the cruise mode outputs.
	 * This method gets called when the drone is in cruise mode.
	 *
	 * @param thrust The input thrust.
	 * @param outputs The PID outputs.
	 */
	void handleCruiseMode(float thrust, Vec3 outputs);

private:
	Servo m_LeftRotor;
	Servo m_RightRotor;

	Servo m_LeftWingServo;
	Servo m_RightWingServo;

	Servo m_ElevatorServo;
	Servo m_RudderServo;

	int m_LeftRotorThrust = 0;
	int m_RightRotorThrust = 0;

	int m_LeftWingAngle = 90;
	int m_RightWingAngle = 90;

	int m_ElevatorAngle = 90;
	int m_RudderAngle = 90;
};
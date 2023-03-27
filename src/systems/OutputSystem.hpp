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
	Servo m_LeftMotor;
	Servo m_RightMotor;

	Servo m_LeftWingServo;
	Servo m_RightWingServo;

	Servo m_ElevatorServo;
	Servo m_RudderServo;

	int m_LeftMotorThrust = 0;
	int m_RightMotorThrust = 0;

	int m_LeftWingAngle = 90;
	int m_RightWingAngle = 90;

	int m_ElevatorAngle = 90;
	int m_RudderAngle = 90;
};
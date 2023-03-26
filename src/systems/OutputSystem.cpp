// Copyright 2023 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "OutputSystem.hpp"

#include "InputSystem.hpp"
#include "Stabilizer.hpp"

#include "core/Common.hpp"
#include "core/Constants.hpp"

constexpr auto g_MotorMinPWM = 1000;
constexpr auto g_MotorMaxPWM = 2000;

float FitToRange(float value, float fromMax)
{
	return map(value, 0, fromMax, 0, 180);
}

void OutputSystem::initialize()
{
	Serial.println("Initializing the output system.");

	m_LeftMotor.attach(g_LeftMotorPin, g_MotorMinPWM, g_MotorMaxPWM);
	m_RightMotor.attach(g_RightMotorPin, g_MotorMinPWM, g_MotorMaxPWM);

	m_LeftWingServo.attach(g_LeftWingServoPin);
	m_RightWingServo.attach(g_RightWingServoPin);

	m_ElevatorServo.attach(g_ElevatorServoPin);
	m_RudderServo.attach(g_RudderServoPin);

	Serial.println("Output system initialized.");
}

void OutputSystem::update()
{
	const auto inputThrust = InputSystem::Instance().getThrust();
	const auto inputPitch = InputSystem::Instance().getPitch();
	const auto inputRoll = InputSystem::Instance().getRoll();
	const auto inputYaw = InputSystem::Instance().getYaw();

	const auto outputs = Stabilizer::Instance().computeOutputs(inputThrust, inputPitch, inputRoll, inputYaw);

	float leftMotorThrust = inputThrust;
	float rightMotorThrust = inputThrust;

	float leftWingAngle = inputYaw + (Stabilizer::Instance().yawValue() * 10);
	float rightWingAngle = /*100 - */ leftWingAngle;

	Serial.print("LMT: ");
	Serial.print(leftMotorThrust);
	Serial.print(" | RMT: ");
	Serial.print(rightMotorThrust);
	Serial.print(" | LWA: ");
	Serial.print(leftWingAngle);
	Serial.print(" | RWA: ");
	Serial.print(rightWingAngle);
	Serial.print(" | Pitch: ");
	Serial.print(outputs.m_Pitch);
	Serial.print(" | Roll: ");
	Serial.print(outputs.m_Roll);
	Serial.print(" | Yaw: ");
	Serial.print(outputs.m_Yaw);
	Serial.println();

	m_LeftMotor.write(FitToRange(leftMotorThrust, g_ThrottleInputMaximum));
	m_RightMotor.write(FitToRange(rightMotorThrust, g_ThrottleInputMaximum));

	m_LeftWingServo.write(map(leftWingAngle, g_RotationalInputMinimum, g_RotationalInputMaximum, 0, 180));
	m_RightWingServo.write(map(rightWingAngle, g_RotationalInputMinimum, g_RotationalInputMaximum, 0, 180));
}

void OutputSystem::writeToAll()
{
	m_LeftMotor.write(m_LeftMotorThrust);
	m_RightMotor.write(m_RightMotorThrust);

	m_LeftWingServo.write(m_LeftWingAngle);
	m_RightWingServo.write(m_RightWingAngle);

	m_ElevatorServo.write(m_ElevatorAngle);
	m_RudderServo.write(m_RudderAngle);
}

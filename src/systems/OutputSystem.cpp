// Copyright 2023 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "OutputSystem.hpp"

constexpr auto g_MotorMinPWM = 1000;
constexpr auto g_MotorMaxPWM = 2000;

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

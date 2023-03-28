// Copyright 2023 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "OutputSystem.hpp"

#include "InputSystem.hpp"
#include "Stabilizer.hpp"

#include "core/Common.hpp"
#include "core/Constants.hpp"
#include "core/GlobalState.hpp"

constexpr auto g_RotorMinPWM = 1000;
constexpr auto g_RotorMaxPWM = 2000;

constexpr auto g_ServoMinimum = 0;
constexpr auto g_ServoMaximum = 180;

constexpr auto g_InputMidValue = 90;

void OutputSystem::initialize()
{
	Serial.println("Initializing the output system.");

	// Attach the rotors.
	m_LeftRotor.attach(g_LeftRotorPin, g_RotorMinPWM, g_RotorMaxPWM);
	m_RightRotor.attach(g_RightRotorPin, g_RotorMinPWM, g_RotorMaxPWM);

	// Attach the wing servos.
	m_LeftWingServo.attach(g_LeftWingServoPin);
	m_RightWingServo.attach(g_RightWingServoPin);
	// pinMode(g_LeftWingServoPin, OUTPUT);
	// pinMode(g_RightWingServoPin, OUTPUT);

	// Attach the elevator and rudder.
	m_ElevatorServo.attach(g_ElevatorServoPin);
	m_RudderServo.attach(g_RudderServoPin);

	// Write the default values to the servos.
	m_LeftWingServo.write(g_WingServoOffsetHover);
	m_RightWingServo.write(g_WingServoOffsetHover);
	m_ElevatorServo.write(g_ElevatorOffset);
	m_RudderServo.write(g_RudderOffset);

	Serial.println("Output system initialized.");
}

void OutputSystem::update()
{
	// Control algorithm
	// Throttle is controlled by the rotor speed.
	//
	// Hover mode:
	// * Pitch is controlled by the wing servos. The servos can both move front or back depending on the pitch.
	// * Roll is controlled by the rotors. More thrust in either one of the rotors will result in the roll.
	// * Yaw is controlled by the wing servos. The servos will move in opposite directions and thus rotating the drone.
	// * The wing servos have an offset of 45 degrees.
	// * The elevator and rudder servos are disabled (not used).
	//
	// Cruise mode:
	// * Pitch is controlled by the wing servos. The servos can both move up or down depending on the pitch. The elevator will also help with pitch.
	// * Roll is controlled by the wing servos. The servos will move in opposite directions (up and down) and thus rolling the drone.
	// * Yaw is controlled by the rotors. More thrust in either one of the rotors will result in teh roll. The rudder will also help with yaw.
	// * The wing servos have an offset of 135 degrees.

	const auto inputThrust = InputSystem::Instance().getThrust();
	const auto inputPitch = InputSystem::Instance().getPitch();
	const auto inputRoll = InputSystem::Instance().getRoll();
	const auto inputYaw = InputSystem::Instance().getYaw();

	const auto outputs = Stabilizer::Instance().computeOutputs(inputThrust, inputPitch, inputRoll, inputYaw);

	if (g_CurrentFlyMode == FlyMode::Hover)
		handleHoverMode(inputThrust, outputs);
	else
		handleCruiseMode(inputThrust, outputs);
}

void OutputSystem::handleHoverMode(float thrust, Vec3 outputs)
{
	// Outputs range: -90 - 90
	// Thrust range: 0 - 1000
	// Servo range: 0 - 180

	const auto mappedThrust = map(thrust, g_ThrottleInputMinimum, g_ThrottleInputMaximum, g_ServoMinimum, g_ServoMaximum);

	float leftRotorThrust = mappedThrust;
	float rightRotorThrust = mappedThrust;

	float leftWingAngle = g_WingServoOffsetHover;
	float rightWingAngle = g_WingServoOffsetHover;

	// Handle pitch
	leftWingAngle += outputs.m_Pitch;
	rightWingAngle += outputs.m_Pitch;

	// Handle yaw
	leftWingAngle -= outputs.m_Yaw;
	rightWingAngle += outputs.m_Yaw;

	// Handle roll
	leftRotorThrust += outputs.m_Roll;
	rightRotorThrust -= outputs.m_Roll;

	// Clamp the values to the requried ranges.
	leftWingAngle = clamp(static_cast<int>(leftWingAngle), g_ServoMinimum, g_ServoMaximum);
	rightWingAngle = clamp(static_cast<int>(rightWingAngle), g_ServoMinimum, g_ServoMaximum);

	leftRotorThrust = clamp(static_cast<int>(leftRotorThrust), g_ServoMinimum, g_ServoMaximum);
	rightRotorThrust = clamp(static_cast<int>(rightRotorThrust), g_ServoMinimum, g_ServoMaximum);

	Serial.print("LMT: ");
	Serial.print(leftRotorThrust);
	Serial.print(" | RMT: ");
	Serial.print(rightRotorThrust);
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

	// Write to the rotors
	m_LeftRotor.write(leftRotorThrust);
	m_RightRotor.write(rightRotorThrust);

	// Write to the wing servos.
	m_LeftWingServo.write(leftWingAngle);
	m_RightWingServo.write(rightWingAngle);
	// analogWrite(g_LeftWingServoPin, map(leftWingAngle, g_RotationalInputMinimum, g_RotationalInputMaximum, 0, 255));
	// analogWrite(g_RightWingServoPin, map(rightWingAngle, g_RotationalInputMinimum, g_RotationalInputMaximum, 0, 255));
	// analogWrite(g_LeftWingServoPin, 255);
	// analogWrite(g_RightWingServoPin, 255);

	// Write to the elevator and rudder.
	m_ElevatorServo.write(g_ElevatorOffset);
	m_RudderServo.write(g_RudderOffset);
}

void OutputSystem::handleCruiseMode(float thrust, Vec3 outputs)
{
	// Outputs range: -90 - 90
	// Thrust range: 0 - 1000
	// Servo range: 0 - 180

	const auto mappedThrust = map(thrust, g_ThrottleInputMinimum, g_ThrottleInputMaximum, g_ServoMinimum, g_ServoMaximum);

	float leftRotorThrust = mappedThrust;
	float rightRotorThrust = mappedThrust;

	float leftWingAngle = g_WingServoOffsetCruise;
	float rightWingAngle = g_WingServoOffsetCruise;

	float elevatorAngle = g_ElevatorOffset;
	float rudderAngle = g_RudderOffset;

	// Handle pitch
	// Handle yaw
	// Handle roll

	// Write to the rotors
	m_LeftRotor.write(leftRotorThrust);
	m_RightRotor.write(rightRotorThrust);

	// Write to the wing servos.
	m_LeftWingServo.write(leftWingAngle);
	m_RightWingServo.write(rightWingAngle);

	// Write to the elevator and rudder.
	m_ElevatorServo.write(elevatorAngle);
	m_RudderServo.write(rudderAngle);
}

// Copyright 2023 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "FSi6DataLink.hpp"

#include "core/Constants.hpp"

#include <Arduino.h>

void FSi6DataLink::onInitialize()
{
	m_Connection.begin(Serial2);
}

void FSi6DataLink::onUpdate()
{
	// Noting to do here.
}

float FSi6DataLink::onGetThrust()
{
	return readChannel(g_ThrustChannel, g_ThrottleInputMinimum, g_ThrottleInputMaximum, g_ThrottleInputMinimum);
}

float FSi6DataLink::onGetPitch()
{
	return readChannel(g_PitchChannel, g_PitchInputMinimum, g_PitchInputMaximum, g_PitchInputMinimum);
}

float FSi6DataLink::onGetRoll()
{
	return readChannel(g_RollChannel, g_RollInputMinimum, g_RollInputMaximum, g_RollInputMinimum);
}

float FSi6DataLink::onGetYaw()
{
	return readChannel(g_YawChannel, g_YawInputMinimum, g_YawInputMaximum, g_YawInputMinimum);
}

int FSi6DataLink::readChannel(uint8_t channel, int minimum, int maximum, int defaultValue)
{
	const auto value = m_Connection.readChannel(channel);
	if (value < 100)
		return defaultValue;

	return map(value, g_ChannelMinimum, g_ChannelMaximum, minimum, maximum);
}

bool FSi6DataLink::readChannelBool(uint8_t channel, bool defaultValue)
{
	const auto value = readChannel(channel, g_ChannelMinimum, g_ChannelMaximum, defaultValue ? 1 : -1);
	return value > 0;
}

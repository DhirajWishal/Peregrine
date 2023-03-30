// Copyright 2023 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "FSi6DataLink.hpp"

#include "core/Constants.hpp"
#include "core/Logging.hpp"

void FSi6DataLink::onInitialize()
{
	PEREGRINE_PRINTLN("Initializing the FS-i6 data link.");

	m_Connection.begin(Serial2);

	PEREGRINE_PRINTLN("The FS-i6 data link initialized.");
}

void FSi6DataLink::onUpdate()
{
	m_Throttle = readChannel(FSi6InputChannel::Throttle, g_ThrottleInputMinimum, g_ThrottleInputMaximum, g_ThrottleInputMinimum);
	m_Pitch = readChannel(FSi6InputChannel::Pitch, g_PitchInputMinimum, g_PitchInputMaximum, g_PitchInputMinimum);
	m_Roll = readChannel(FSi6InputChannel::Roll, g_RollInputMinimum, g_RollInputMaximum, g_RollInputMinimum);
	m_Yaw = readChannel(FSi6InputChannel::Yaw, g_YawInputMinimum, g_YawInputMaximum, g_YawInputMinimum);
	
	g_RequiredFlyMode = readChannelBool(FSi6InputChannel::Aux1, true) ? FlyMode::Cruise : FlyMode::Hover;
	g_CurrentFlyMode = g_RequiredFlyMode;
}

int FSi6DataLink::readChannel(FSi6InputChannel channel, int minimum, int maximum, int defaultValue)
{
	const auto value = m_Connection.readChannel(static_cast<uint8_t>(channel));
	if (value < 100)
		return defaultValue;

	return map(value, g_ChannelMinimum, g_ChannelMaximum, minimum, maximum);
}

bool FSi6DataLink::readChannelBool(FSi6InputChannel channel, bool defaultValue)
{
	const auto value = readChannel(channel, g_ChannelMinimum, g_ChannelMaximum, defaultValue ? 1 : -1);

	constexpr auto midValue = (g_ChannelMinimum + ((g_ChannelMaximum - g_ChannelMinimum) / 2));
	return value > midValue;
}

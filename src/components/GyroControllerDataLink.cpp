// Copyright 2023 Nexonous
// SPDX-License-Identifier: Apache-2.0

#include <SPI.h>
#include "GyroControllerDataLink.hpp"

#ifdef PEREGRINE_DEBUG
#include "printf.h"

#endif

#include "core/Logging.hpp"
#include "core/Constants.hpp"

GyroControllerDataLink::GyroControllerDataLink()
	: m_Transceiver(g_ChipEnablePin, g_ChipSelectNotPin), m_ThrottleValue(g_ThrottleInputMinimum)
{
}

void GyroControllerDataLink::onInitialize()
{
	PEREGRINE_PRINTLN("Initializing the nRF24L01 transceiver.");

	if (!m_Transceiver.begin())
	{
		PEREGRINE_PRINTLN("Failed to initialize the nRF24L01 transceiver!");
		return;
	}

	m_Transceiver.setDataRate(RF24_250KBPS);
	m_Transceiver.setPALevel(RF24_PA_MAX);
	m_Transceiver.setAutoAck(false);
	m_Transceiver.setRetries(5, 15);

	m_Transceiver.openReadingPipe(1, g_DefaultAddress);
	m_Transceiver.startListening();

#ifdef PEREGRINE_DEBUG
	printf_begin();
	m_Transceiver.printPrettyDetails();

#endif

	PEREGRINE_PRINTLN("The nRF24L01 transceiver is initialized.");
}

void GyroControllerDataLink::onUpdate()
{
	if (m_Transceiver.available())
	{
		m_Transceiver.read(&m_Payload, sizeof(m_Payload));

		// Process the throttle value.
		m_ThrottleValue += m_Payload.m_Throttle - g_ThrottleInputMiddle;
	}
}

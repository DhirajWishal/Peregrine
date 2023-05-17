// Copyright 2023 Nexonous
// SPDX-License-Identifier: Apache-2.0

#include <SPI.h>
#include "nRF24L01DataLink.hpp"

#ifdef PEREGRINE_DEBUG
#include "printf.h"

#endif

#include "core/Logging.hpp"

nRF24L01DataLink::nRF24L01DataLink()
	: m_Transceiver(g_ChipEnablePin, g_ChipSelectNotPin)
{
}

void nRF24L01DataLink::onInitialize()
{
	PEREGRINE_PRINTLN("Initializing the nRF24L01 transceiver.");

	if (!m_Transceiver.begin())
	{
		PEREGRINE_PRINTLN("Failed to initialize the nRF24L01 transceiver!");
		return;
	}

	m_Transceiver.setDataRate(RF24_250KBPS);

	m_Transceiver.openReadingPipe(0, g_DefaultAddress);
	m_Transceiver.startListening();

#ifdef PEREGRINE_DEBUG
	m_Transceiver.setAutoAck(1);
	m_Transceiver.enableAckPayload();
	m_Transceiver.setRetries(5, 15);
	m_Transceiver.setPALevel(RF24_PA_MIN);

	printf_begin();
	m_Transceiver.printPrettyDetails();

#endif

	PEREGRINE_PRINTLN("The nRF24L01 transceiver is initialized.");
}

void nRF24L01DataLink::onUpdate()
{
	if (m_Transceiver.available())
		m_Transceiver.read(&m_Payload, sizeof(m_Payload));
}

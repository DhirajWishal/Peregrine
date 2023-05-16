// Copyright 2023 Nexonous
// SPDX-License-Identifier: Apache-2.0

#include "nRF24L01DataLink.hpp"

#include "core/Logging.hpp"

nRF24L01DataLink::nRF24L01DataLink()
	: m_Transceiver(g_ChipEnablePin, g_ChipSelectNotPin)
{
}

void nRF24L01DataLink::onInitialize()
{
	PEREGRINE_PRINTLN("Initializing the nRF24L01 transceiver.");

	m_Transceiver.begin();
	m_Transceiver.openReadingPipe(0, g_DefaultAddress);
	m_Transceiver.startListening();

	PEREGRINE_PRINTLN("The nRF24L01 transceiver is initialized.");
}

void nRF24L01DataLink::onUpdate()
{
	if (m_Transceiver.available())
		m_Transceiver.read(&m_Payload, sizeof(m_Payload));
}

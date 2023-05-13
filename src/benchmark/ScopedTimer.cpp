// Copyright 2023 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "ScopedTimer.hpp"

ScopedTimer::ScopedTimer()
	: m_Time(micros())
{
}

ScopedTimer::ScopedTimer(size_t line, const char *file, const char *signature)
	: m_Line(line), m_File(file), m_Signature(signature), m_Time(micros())
{
}

ScopedTimer::~ScopedTimer()
{
	const auto currentTime = micros();
	const auto difference = currentTime - m_Time;

	if (m_File && m_Signature)
		PEREGRINE_PRINTF("ScopedTimer(line: %u, file: \"%s\", signature: \"%s\"): %u us\n", m_Line, m_File, m_Signature, difference);

	else
		PEREGRINE_PRINTF("ScopedTimer(): %u us\n", difference);
}

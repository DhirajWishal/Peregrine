// Copyright 2023 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "core/Logging.hpp"

/**
 * @brief Scoped timer class.
 * This class starts a timer and prints it out to the console when gone out of scope.
 */
class ScopedTimer final
{
public:
	/**
	 * @brief Construct a new Scoped Timer object.
	 */
	ScopedTimer();

	/**
	 * @brief Construct a new Scoped Timer object.
	 *
	 * @param line The line number of the timer instance.
	 * @param file The file name of the timer instance.
	 * @param signature The function signature where the timer was initialized.
	 */
	explicit ScopedTimer(size_t line, const char *file, const char *signature);

	/**
	 * @brief Destroy the Scoped Timer object.
	 */
	~ScopedTimer();

private:
	size_t m_Line = 0;
	const char *m_File = nullptr;
	const char *m_Signature = nullptr;

	unsigned long m_Time = 0;
};

#define CONCAT_HELPER(X,Y) X##Y 
#define CONCAT(arg1, arg2) CONCAT_HELPER(arg1, arg2)

#if defined(PEREGRINE_DEBUG) || defined(PEREGRINE_PRODUCTION_TEST)
#define PEREGRINE_SETUP_SCOPED_TIMER() const auto CONCAT(_scopedTimer_, __LINE__) = ::ScopedTimer(__LINE__, __FILE__, __PRETTY_FUNCTION__)	

#else
#define PEREGRINE_SETUP_SCOPED_TIMER() NoOp()

#endif
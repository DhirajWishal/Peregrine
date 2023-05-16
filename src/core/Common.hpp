// Copyright 2023 Nexonous
// SPDX-License-Identifier: Apache-2.0

#pragma once

inline float map(float x, float in_min, float in_max, float out_min, float out_max)
{
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

template <class Type>
inline Type clamp(Type input, Type min, Type max)
{
	if (input < min)
		return min;
	if (input > max)
		return max;

	return input;
}
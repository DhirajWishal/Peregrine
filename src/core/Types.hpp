// Copyright 2023 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

/**
 * @brief Vec3 type.
 * This is a 3 component vector type.
 */
struct Vec3 final
{
	Vec3() = default;
	Vec3(float value) : m_X(value), m_Y(value), m_Z(value) {}
	Vec3(float x, float y, float z) : m_X(x), m_Y(y), m_Z(z) {}

	union
	{
		struct
		{
			float m_X;
			float m_Y;
			float m_Z;
		};
		struct
		{
			float m_Pitch;
			float m_Yaw;
			float m_Roll;
		};
	};
};
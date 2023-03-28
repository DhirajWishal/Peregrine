// Copyright 2023 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

/**
 * @brief Vec3 type.
 * This is a 3 component vector type.
 */
struct Vec3 final
{
	Vec3() : m_X(0.0f), m_Y(0.0f), m_Z(0.0f) {}
	explicit Vec3(float value) : m_X(value), m_Y(value), m_Z(value) {}
	explicit Vec3(float x, float y, float z) : m_X(x), m_Y(y), m_Z(z) {}

	[[nodiscard]] Vec3 operator-(const Vec3 &other) const { return Vec3(m_X - other.m_X, m_Y - other.m_Y, m_Z - other.m_Z); }

	Vec3 &operator-=(const Vec3 &other)
	{
		m_X -= other.m_X;
		m_Y -= other.m_Y;
		m_Z -= other.m_Z;
		return *this;
	}

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
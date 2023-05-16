// Copyright 2023 Nexonous
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

/**
 * @brief Vec4 type.
 * This is a 4 component vector type.
 */
struct Vec4 final
{
	Vec4() : m_X(0.0f), m_Y(0.0f), m_Z(0.0f), m_W(0.0f) {}
	explicit Vec4(float value) : m_X(value), m_Y(value), m_Z(value), m_W(value) {}
	explicit Vec4(float x, float y, float z, float w) : m_X(x), m_Y(y), m_Z(z), m_W(w) {}

	explicit Vec4(const Vec3 &vec) : m_X(vec.m_X), m_Y(vec.m_Y), m_Z(vec.m_Z), m_W(0.0f) {}
	explicit Vec4(const Vec3 &vec, float w) : m_X(vec.m_X), m_Y(vec.m_Y), m_Z(vec.m_Z), m_W(w) {}
	explicit Vec4(float x, const Vec3 &vec) : m_X(x), m_Y(vec.m_X), m_Z(vec.m_Y), m_W(vec.m_Z) {}

	[[nodiscard]] Vec4 operator-(const Vec4 &other) const { return Vec4(m_X - other.m_X, m_Y - other.m_Y, m_Z - other.m_Z, m_W - other.m_W); }

	Vec4 &operator-=(const Vec4 &other)
	{
		m_X -= other.m_X;
		m_Y -= other.m_Y;
		m_Z -= other.m_Z;
		m_W -= other.m_W;
		return *this;
	}

	union
	{
		struct
		{
			float m_X;
			float m_Y;
			float m_Z;
			float m_W;
		};
		struct
		{
			float m_Pitch;
			float m_Yaw;
			float m_Roll;
			float m_Throttle;
		};
	};
};
// Copyright 2023 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

// Ref: https://github.com/TKJElectronics/KalmanFilter/blob/master/Kalman.cpp

#include "KalmanFilter.hpp"

void KalmanFilter::setAngle(float angle)
{
	m_Angle = angle;
}

float KalmanFilter::compute(float angle, float rate, float delta)
{
	// Setup the initial angle if we don't have it already.
	if (!m_isInitialized)
	{
		m_Angle = angle;
		m_isInitialized = true;
	}

	m_Rate = rate - m_Bias;
	m_Angle += delta * rate;

	m_ErrorMatrix[0][0] += delta * (delta * m_ErrorMatrix[1][1] - m_ErrorMatrix[0][1] - m_ErrorMatrix[1][0] + m_ConstantAngle);
	m_ErrorMatrix[0][1] -= delta * m_ErrorMatrix[1][1];
	m_ErrorMatrix[1][0] -= delta * m_ErrorMatrix[1][1];
	m_ErrorMatrix[1][1] += m_ConstantBias * delta;

	const auto S = m_ErrorMatrix[0][0] + m_Measure;

	float K[2];
	K[0] = m_ErrorMatrix[0][0] / S;
	K[1] = m_ErrorMatrix[1][0] / S;

	const auto y = angle - m_Angle;

	m_Angle += K[0] * y;
	m_Bias += K[1] * y;

	const auto P00_temp = m_ErrorMatrix[0][0];
	const auto P01_temp = m_ErrorMatrix[0][1];

	m_ErrorMatrix[0][0] -= K[0] * P00_temp;
	m_ErrorMatrix[0][1] -= K[0] * P01_temp;
	m_ErrorMatrix[1][0] -= K[1] * P00_temp;
	m_ErrorMatrix[1][1] -= K[1] * P01_temp;

	return m_Angle;
}

void KalmanFilter::tune(float angle, float bias, float measure)
{
	m_ConstantAngle = angle;
	m_ConstantBias = bias;
	m_Measure = measure;
}

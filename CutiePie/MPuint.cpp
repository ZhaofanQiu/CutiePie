#include "stdafx.h"

#include "MultiPrecision.h"

#include <string>

namespace MP
{
	MPuint::MPuint()
	{
		m_length = 0;
	}

	MPuint::MPuint(LPuint lpu)
	{
		m_length = 1;
		m_A[0] = lpu;
	}

	MPuint::MPuint(MPuint& mpu)
	{
		m_length = mpu.m_length;
		memcpy(m_A, mpu.m_A, sizeof(LPuint)* m_length);
	}
}

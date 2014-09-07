#include "stdafx.h"

#include "MultiPrecision.h"

namespace MP
{
	bool MPuint::operator==(const MPuint& mpu) const
	{
		if (m_data.len != mpu.m_data.len)
			return false;
		if (memcmp(m_data.A, mpu.m_data.A, m_data.len * sizeof(LPuint)) == 0)
			return true;
		return false;
	}
	bool MPuint::operator==(const LPuint& lpu) const
	{
		if (m_data.len != 1)
			return false;
		if (m_data.A[0] == lpu)
			return true;
		return false;
	}
	bool MPuint::operator>(const MPuint& mpu) const
	{
		if (m_data.len > mpu.m_data.len)
			return true;
		if (m_data.len < mpu.m_data.len)
			return false;
		LPuint *a1 = m_data.A, *a2 = mpu.m_data.A;
		for (int i = m_data.len - 1; i >= 0; i--)
		{
			if (a1[i] > a2[i])
				return true;
			if (a1[i] < a2[i])
				return false;
		}
		return true;
	}
	bool MPuint::operator>(const LPuint& lpu) const
	{
		if (m_data.len > 1)
			return true;
		if (m_data.len == 0)
			return false;
		if (m_data.A[0] >= lpu)
			return true;
		else
			return false;
	}
	bool MPuint::operator<(const MPuint& mpu) const
	{
		return !operator>(mpu);
	}
	bool MPuint::operator<(const LPuint& lpu) const
	{
		return !operator>(lpu);
	}
	bool MPuint::operator!=(const MPuint& mpu) const
	{
		return !operator==(mpu);
	}
	bool MPuint::operator!=(const LPuint& lpu) const
	{
		return !operator==(lpu);
	}
}
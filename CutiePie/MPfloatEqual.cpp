#include "stdafx.h"

#include "MultiPrecision.h"

#include <algorithm>

namespace MP
{
	bool MPfloat::operator==(const MPfloat& mpf) const
	{
		if (m_data.len == 0 && mpf.m_data.len == 0)
			return true;

		if (m_data.len + m_data.exp != mpf.m_data.len + mpf.m_data.exp)
		{
			return false;
		}
		int l = m_data.len;
		if (mpf.m_data.len < l)
			l = mpf.m_data.len;
		if (memcmp(m_data.A + m_data.len - l, mpf.m_data.A + mpf.m_data.len - l, l) == 0)
			return true;
		return false;
	}
	bool MPfloat::operator!=(const MPfloat& mpf) const
	{
		return !operator==(mpf);
	}
	bool MPfloat::operator>(const MPfloat& mpf) const
	{
		if (m_data.len + m_data.exp > mpf.m_data.len + mpf.m_data.exp)
			return true;
		if (m_data.len + m_data.exp < mpf.m_data.len + mpf.m_data.exp)
			return false;
		LPuint *a1 = m_data.A, *a2 = mpf.m_data.A;
		for (int i = m_data.len + m_data.exp - 1; i >= std::max(m_data.exp, mpf.m_data.exp); i--)
		{
			if (a1[i - m_data.exp] > a2[i - mpf.m_data.exp])
				return true;
			if (a1[i - m_data.exp] < a2[i - mpf.m_data.exp])
				return false;
		}
		if (m_data.len > mpf.m_data.len)
			return true;
		else
			return false;
		return true;
	}
	bool MPfloat::operator<(const MPfloat& mpf) const
	{
		return !operator>(mpf);
	}
}
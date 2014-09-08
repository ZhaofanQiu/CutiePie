#include "stdafx.h"

#include "MultiPrecision.h"

#include <intrin.h>

namespace MP
{
	MPuint MPuint::operator-(const MPuint& mpu) const
	{
		LPuint *a1 = m_data.A, *a2 = mpu.m_data.A;
		int l1 = m_data.len, l2 = mpu.m_data.len;
		MPuint out(l1);
		LPuint *a3 = out.m_data.A;

		out.m_data.len = l1;
		unsigned char rem = 0;
		for (int i = 0; i < l2; i++)
		{
			rem = _subborrow_u64(rem, a1[i], a2[i], a3 + i);
		}
		if (rem == 0)
			memcpy(a3 + l2, a1 + l2, (l1 - l2) * sizeof(LPuint));
		else
		{
			for (int i = l2; i < l1; i++)
			{
				rem = _subborrow_u64(rem, a1[i], 0, a3 + i);
			}
		}
		while ((out.m_data.len > 0) && (a3[out.m_data.len - 1] == 0))
			out.m_data.len--;
		return out;
	}
	MPuint MPuint::operator-(const LPuint& lpu)const
	{
		MPuint temp(lpu);
		return operator-(temp);
	}
}
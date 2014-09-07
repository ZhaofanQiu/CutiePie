#include "stdafx.h"

#include "MultiPrecision.h"

#include <intrin.h>

namespace MP
{
	MPuint MPuint::operator*(const MPuint& mpu)
	{
		LPuint *a1 = m_data.A, *a2 = mpu.m_data.A;
		int l1 = m_data.len, l2 = mpu.m_data.len;
		MPuint out(l1 + l2 + 1);

		LPuint *a3 = out.m_data.A;
		out.m_data.len = l1 + l2 - 1;
		
		LPuint sup = 0, sup2 = 0, up, low;
		LPuint *pup = &up, *psup = &sup, *psup2 = &sup2;
		unsigned char rem = 0, rem2 = 0;
		for (int i = 0; i < l1 + l2 - 1; i++)
		{
			a3[i] = sup;
			sup = sup2;
			sup2 = 0;
			int j = 0;
			if (j <= i - l2)
			{
				j = i - l2 + 1;
			}
			for (; j < l1 && j <= i; j++)
			{
				int k = i - j;
				low = _umul128(a1[j], a2[k], pup);

				rem = _addcarry_u64(0, a3[i], low, a3 + i);

				rem2 = _addcarry_u64(rem, sup, up, psup);

				_addcarry_u64(rem2, sup2, 0, psup2);
			}
		}
		if (sup != 0)
		{
			out.m_data.len++;
			a3[out.m_data.len - 1] = sup;
		}
		if (sup2 != 0)
		{
			out.m_data.len++;
			a3[out.m_data.len - 1] = sup2;
		}
		return out;
	}
	MPuint MPuint::operator*(const LPuint& lpu)
	{
		MPuint temp(lpu);
		return operator*(temp);
	}
}
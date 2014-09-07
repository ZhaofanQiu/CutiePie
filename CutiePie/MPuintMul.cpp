#include "stdafx.h"

#include "MultiPrecision.h"

#include <intrin.h>

namespace MP
{
	MPuint MPuint::operator*(const MPuint& mpu)
	{
		MPuint out;
		
		LPuint *a1 = m_data->A, *a2 = mpu.m_data->A, *a3 = out.m_data->A;
		int l1 = m_data->len, l2 = mpu.m_data->len;

		out.m_data->len = l1 + l2 - 1;
		
		LPuint sup = 0, sup2 = 0, up, low;
		unsigned char rem = 0, rem2 = 0, rem3 = 0;
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
				low = _umul128(a1[j], a2[k], &up);
				rem2 = _addcarry_u64(0, sup, up, &sup);
				sup2 += rem2;
				rem = _addcarry_u64(0, a3[i], low, a3 + i);
				rem3 = _addcarry_u64(rem, sup, 0, &sup);
				sup2 += rem3;
			}
		}
		if (sup != 0)
		{
			out.m_data->len++;
			a3[out.m_data->len - 1] = sup;
		}
		if (sup2 != 0)
		{
			out.m_data->len++;
			a3[out.m_data->len - 1] = sup2;
		}
		return out;
	}
	MPuint MPuint::operator*(const LPuint& lpu)
	{
		MPuint temp(lpu);
		return operator*(temp);
	}
}
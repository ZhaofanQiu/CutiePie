#include "stdafx.h"

#include "MultiPrecision.h"

#include <intrin.h>

#include <algorithm>

namespace MP
{
	MPuint MPuint::operator+(const MPuint& mpu)const
	{
		LPuint *a1 = m_data.A, *a2 = mpu.m_data.A;
		int l1 = m_data.len, l2 = mpu.m_data.len;
		MPuint out(std::max(l1, l2) + 1);

		LPuint *a3 = out.m_data.A;
		if (l1 <= l2)
		{
			out.m_data.len = l2;
			unsigned char rem = 0;
			for (int i = 0; i < l1; i++)
			{
				rem = _addcarry_u64(rem, a1[i], a2[i], a3 + i);
			}
			if (rem == 0)
				memcpy(a3 + l1, a2 + l1, (l2 - l1) * sizeof(LPuint));
			else
			{
				if (l1 != l2)
				{
					for (int i = l1; i < l2; i++)
					{
						rem = _addcarry_u64(rem, 0, a2[i], a3 + i);
					}
				}
				if (rem != 0)
				{
					a3[l2] = rem;
					out.m_data.len++;
				}
			}
		}
		else
		{
			out.m_data.len = l1;
			unsigned char rem = 0;
			for (int i = 0; i < l2; i++)
			{
				rem = _addcarry_u64(rem, a1[i], a2[i], a3 + i);
			}
			if (rem == 0)
				memcpy(a3 + l2, a1 + l2, (l1 - l2) * sizeof(LPuint));
			else
			{
				for (int i = l2; i < l1; i++)
				{
					rem = _addcarry_u64(rem, 0, a1[i], a3 + i);
				}
				if (rem != 0)
				{
					a3[l1] = rem;
					out.m_data.len++;
				}
			}
		}
		return out;
	}

	MPuint MPuint::operator+(const LPuint& lpu)const
	{
		MPuint out(m_data.len + 1);
		LPuint *a1 = m_data.A, *a2 = out.m_data.A;

		if (m_data.len == 0)
		{
			out.m_data.len = 1;
			a2[0] = lpu;
		}
		else
		{
			unsigned char rem = 0;
			out.m_data.len = m_data.len;

			rem = _addcarry_u64(rem, a1[0], lpu, a2);
			int i = 1;
			while (rem != 0 && i < m_data.len)
			{
				rem = _addcarry_u64(rem, a1[i], 0, a2 + i);
				i++;
			}
			if (rem != 0)
			{
				out.m_data.len++;
				a2[out.m_data.len - 1] = rem;
			}
			else
				memcpy(a2 + i, a1 + i, (out.m_data.len - i) * sizeof(LPuint));
		}
		return out;
	}

}
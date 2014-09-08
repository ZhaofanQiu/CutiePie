#include "stdafx.h"

#include "MultiPrecision.h"

#include <algorithm>
#include <thread>

namespace MP
{
	MPuint MpAdd(const MPuint& mpf1, const MPuint& mpf2, int exp)
	{
		LPuint *a1 = mpf1.m_data.A, *a2 = mpf2.m_data.A;
		int l1 = mpf1.m_data.len, l2 = mpf2.m_data.len;

		MPuint out(std::max(l1, l2 + exp) + 1);

		LPuint *a3 = out.m_data.A;

		out.m_data.len = std::max(l1, l2 + exp);

		unsigned char rem = 0;

		for (int i = 0; i < out.m_data.len; i++)
		{
			bool in1 = (i < l1);
			bool in2 = (i >= exp && i < exp + l2);
			if (in1 && in2)
			{
				rem = _addcarry_u64(rem, a1[i], a2[i - exp], a3 + i);
			}
			else
			{
				if (in1 && !in2)
				{
					rem = _addcarry_u64(rem, a1[i], 0, a3 + i);
				}
				else
				{
					if (!in1 && in2)
						rem = _addcarry_u64(rem, 0, a2[i - exp], a3 + i);
					else
						rem = _addcarry_u64(rem, 0, 0, a3 + i);
				}
			}
		}
		if (rem != 0)
		{
			out.m_data.len++;
			out.m_data.A[out.m_data.len - 1] = rem;
		}
		return out;
	}
	void MpMul(MPfloat& res, const MPfloat& mpf1, const MPfloat& mpf2)
	{
		res = mpf1 * mpf2;
	}
	void MpMul2(MPuint& res, const MPuint& mpu1, const MPuint& mpu2)
	{
		res = mpu1 * mpu2;
	}
}

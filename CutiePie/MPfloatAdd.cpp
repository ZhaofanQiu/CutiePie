#include "stdafx.h"

#include "MultiPrecision.h"

#include <algorithm>

namespace MP
{
	MPfloat MPfloat::operator+(const MPfloat& mpf)const
	{
		LPuint *a1 = m_data.A, *a2 = mpf.m_data.A;
		int l1 = m_data.len, l2 = mpf.m_data.len;
		int e1 = m_data.exp, e2 = mpf.m_data.exp;
		MPfloat out(std::max(l1 + e1, l2 + e2) - std::min(e1, e2) + 1);

		LPuint *a3 = out.m_data.A;
		out.m_data.exp = std::min(e1, e2);
		out.m_data.len = std::max(l1 + e1, l2 + e2) - out.m_data.exp;
		int e3 = out.m_data.exp, l3 = out.m_data.len;

		unsigned char rem = 0;

		for (int i = 0; i < out.m_data.len; i++)
		{
			bool in1 = (i + e3 >= e1 && i + e3 < e1 + l1);
			bool in2 = (i + e3 >= e2 && i + e3 < e2 + l2);
			if (in1 && in2)
			{
				rem = _addcarry_u64(rem, a1[i + e3 - e1], a2[i + e3 - e2], a3 + i);
			}
			else
			{
				if (in1 && !in2)
				{
					rem = _addcarry_u64(rem, a1[i + e3 - e1], 0, a3 + i);
				}
				else
				{
					if (!in1 && in2)
						rem = _addcarry_u64(rem, 0, a2[i + e3 - e2], a3 + i);
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
}
#include "stdafx.h"

#include "MultiPrecision.h"
#include "MPmpMul.h"

#include <algorithm>
#include <thread>

namespace MP
{
	MPfloat MPfloat::operator*(const MPfloat& mpf)
	{
		LPuint *a1 = m_data.A, *a2 = mpf.m_data.A;
		int l1 = m_data.len, l2 = mpf.m_data.len;
		int e1 = m_data.exp, e2 = mpf.m_data.exp;

		if (std::min(l1, l2) > 100)
		{
			int k = std::min(l1, l2) / 2;
			MPfloat a11(*this), a12(*this), a21(mpf), a22(mpf);
			a11.m_data.len = k;
			a11.m_data.exp = 0;
			a12.m_data.len = l1 - k;
			a12.m_data.exp = 0;
			a12.m_data.A = a12.m_data.A + k;

			a21.m_data.len = k;
			a21.m_data.exp = 0;
			a22.m_data.len = l2 - k;
			a22.m_data.exp = 0;
			a22.m_data.A = a22.m_data.A + k;


			MPfloat Z0, Z1, Z2;// Z0 = a11 * a21;// Z2 = a12 * a22;
			if (std::min(l1, l2) > 1000)
			{
				std::thread t1(MpMul, std::ref<MPfloat>(Z0), a11, a21);
				std::thread t2(MpMul, std::ref<MPfloat>(Z2), a12, a22);
				Z1 = (a11 + a12) * (a21 + a22);
				t1.join();
				t2.join();
			}
			else
			{
				MpMul(Z0, a11, a21);
				MpMul(Z2, a12, a22);
				Z1 = (a11 + a12) * (a21 + a22);
			}

			Z1 = Z1 - Z0 - Z2;

			Z0.m_data.exp += e1 + e2;
			Z1.m_data.exp += e1 + e2 + k;
			Z2.m_data.exp += e1 + e2 + k + k;
			return Z0 + Z1 + Z2;
		}
		else
		{
			MPfloat out(l1 + l2 + 1);
			LPuint *a3 = out.m_data.A;
			out.m_data.exp = e1 + e2;
			out.m_data.len = l1 + l2 - 1;
			int e3 = out.m_data.exp, l3 = out.m_data.len;
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
	}
	MPfloat MPfloat::operator*(const LPuint& lpf)
	{
		MPfloat temp(lpf, 0);
		return operator*(temp);
	}
}
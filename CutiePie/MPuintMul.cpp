#include "stdafx.h"

#include "MultiPrecision.h"

#include <intrin.h>
#include <algorithm>
#include <thread>
#include "MPmpMul.h"

namespace MP
{
	MPuint MPuint::operator*(const MPuint& mpu)const
	{
		LPuint *a1 = m_data.A, *a2 = mpu.m_data.A;
		int l1 = m_data.len, l2 = mpu.m_data.len;
		int lmin = std::min(l1, l2);
		int lmax = std::max(l1, l2);
		if (lmin > 100)
		{
			int k = lmax / 2;
			if (k >= lmin)
				k = lmin - 1;
			MPuint a11(*this), a12(*this), a21(mpu), a22(mpu);
			a11.m_data.len = k;
			while ((a11.m_data.len > 0) && (a11.m_data.A[a11.m_data.len - 1] == 0))
				a11.m_data.len--;
			a12.m_data.len = l1 - k;
			a12.m_data.A = a12.m_data.A + k;

			a21.m_data.len = k;
			while ((a21.m_data.len > 0) && (a21.m_data.A[a21.m_data.len - 1] == 0))
				a21.m_data.len--;
			a22.m_data.len = l2 - k;
			a22.m_data.A = a22.m_data.A + k;
			
			MPuint Z0, Z1, Z2;// Z0 = a11 * a21;// Z2 = a12 * a22;
			if (std::min(l1, l2) > 2000)
			{
				std::thread t1(MpMul2, std::ref<MPuint>(Z0), a11, a21);
				std::thread t2(MpMul2, std::ref<MPuint>(Z2), a12, a22);
				Z1 = (a11 + a12) * (a21 + a22);
				t1.join();
				t2.join();
			}
			else
			{
				MpMul2(Z0, a11, a21);
				MpMul2(Z2, a12, a22);
				Z1 = (a11 + a12) * (a21 + a22);
			}
			Z1 = (Z1 - Z0) - Z2;

			return MpAdd(MpAdd(Z0, Z1, k), Z2, k + k);
		}
		else
		{
			MPuint out(l1 + l2 + 1);
			LPuint *a3 = out.m_data.A;
			out.m_data.len = l1 + l2 - 1;

			LPuint up, low;
			LPuint *pup = &up;
			unsigned char rem = 0;
			memset(a3, 0, sizeof(LPuint)* (l1 + l2 + 1));
			for (int i = 0; i < l1; i++)
			{
				for (int j = 0; j < l2; j++)
				{
					int k = i + j;
					low = _umul128(a1[i], a2[j], pup);
					rem = _addcarry_u64(0, a3[k], low, a3 + k);
					rem = _addcarry_u64(rem, a3[k + 1], up, a3 + k + 1);
					_addcarry_u64(rem, a3[k + 2], 0, a3 + k + 2);
				}
			}
			if (a3[out.m_data.len] != 0)
			{
				out.m_data.len++;
			}
			if (a3[out.m_data.len] != 0)
			{
				out.m_data.len++;
			}
			return out;
		}
	}
	MPuint MPuint::operator*(const LPuint& lpu)const
	{
		MPuint temp(lpu);
		return operator*(temp);
	}
}
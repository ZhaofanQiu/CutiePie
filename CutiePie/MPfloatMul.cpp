#include "stdafx.h"

#include "MultiPrecision.h"
#include "MPmpMul.h"

#include <algorithm>
#include <thread>
#include "FFT.h"

namespace MP
{
	MPfloat MPfloat::operator*(const MPfloat& mpf)const
	{
		LPuint *a1 = m_data.A, *a2 = mpf.m_data.A;
		int l1 = m_data.len, l2 = mpf.m_data.len;
		int e1 = m_data.exp, e2 = mpf.m_data.exp;
		int lmin = std::min(l1, l2);
		int lmax = std::max(l1, l2);

		if (lmin > 1000)
		{
			MPfloat out(l1 + l2 + 1);
			LPuint *a3 = out.m_data.A;
			out.m_data.exp = e1 + e2;
			out.m_data.len = l1 + l2 - 1;

			int zl = l1 + l2 + 1;

			int k = 0;
			size_t length = 1;
			while (length < 8 * zl){
				length <<= 1;
				k++;
			}

			__m128d* Ta = new __m128d[length], *Tb = new __m128d[length];
			shared_ptr<__m128d> _Ta(Ta, [](__m128d* p){delete[] p; }), _Tb(Tb, [](__m128d* p){delete[] p; });

			FFT::fft_init(k);
			FFT::int_to_fft(Ta, k, a1, l1);
			FFT::int_to_fft(Tb, k, a2, l2);
			std::thread t1(FFT::fft_forward, Ta, k, k);
			std::thread t2(FFT::fft_forward, Tb, k, k);
			t1.join();
			t2.join();
			//FFT::fft_forward(Ta, k);
			//FFT::fft_forward(Tb, k);
			FFT::fft_pointwise(Ta, Tb, k);
			FFT::fft_inverse(Ta, k, k);
			FFT::fft_to_int(Ta, k, a3, zl);
			if (a3[out.m_data.len] != 0)
			{
				out.m_data.len += 1;
			}
			return out;
		}
		else
		{
			if (lmin > 100)
			{
				int k = lmax / 2;
				if (k >= lmin)
					k = lmin - 1;
				MPfloat a11(*this), a12(*this), a21(mpf), a22(mpf);
				a11.m_data.len = k;
				while ((a11.m_data.len > 0) && (a11.m_data.A[a11.m_data.len - 1] == 0))
					a11.m_data.len--;
				a11.m_data.exp = 0;
				a12.m_data.len = l1 - k;
				a12.m_data.exp = 0;
				a12.m_data.A = a12.m_data.A + k;

				a21.m_data.len = k;
				while ((a21.m_data.len > 0) && (a21.m_data.A[a21.m_data.len - 1] == 0))
					a21.m_data.len--;
				a21.m_data.exp = 0;
				a22.m_data.len = l2 - k;
				a22.m_data.exp = 0;
				a22.m_data.A = a22.m_data.A + k;
				
				MPfloat Z0, Z1, Z2;// Z0 = a11 * a21;// Z2 = a12 * a22;
				MpMul(Z0, a11, a21);
				MpMul(Z2, a12, a22);
				Z1 = (a11 + a12) * (a21 + a22);

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

				LPuint up, low;
				LPuint *pup = &up;
				unsigned char rem = 0, rem2 = 0;
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
					out.m_data.len += 1;
				}
				return out;
			}
		}
	}
	MPfloat MPfloat::operator*(const LPuint& lpf)const
	{
		LPuint *a1 = m_data.A;
		int l1 = m_data.len;
		int e1 = m_data.exp;

		MPfloat out(l1 + 2);
		LPuint *a3 = out.m_data.A;
		out.m_data.exp = e1;
		out.m_data.len = l1;

		LPuint up, low;
		LPuint *pup = &up;
		unsigned char rem = 0, rem2 = 0;
		memset(a3, 0, sizeof(LPuint)* (l1 + 2));
		for (int i = 0; i < l1; i++)
		{
			low = _umul128(a1[i], lpf, pup);
			rem = _addcarry_u64(0, a3[i], low, a3 + i);
			rem = _addcarry_u64(rem, a3[i + 1], up, a3 + i + 1);
			_addcarry_u64(rem, a3[i + 2], 0, a3 + i + 2);
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
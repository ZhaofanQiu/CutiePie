#include "stdafx.h"

#include "PiModule.h"

#include <string>

namespace PM
{
	MPfloat PiModule::MPfloatCut(const MPfloat& mpf, int n)
	{
		int n2 = (int)floor(n * log2((double)10) / 64) + 2;
		if (n2 >= mpf.m_data.len)
			return mpf;
		MPfloat out(n2);
		out.m_data.len = n2;
		out.m_data.exp = mpf.m_data.exp + mpf.m_data.len - n2;
		memcpy(out.m_data.A, mpf.m_data.A + mpf.m_data.len - n2, n2 * sizeof(LPuint));
		LPuint max64 = 0xffffffffffffffff;

		if (mpf.m_data.A[mpf.m_data.len - n2 - 1] > max64 / 2)
		{
			out = out + MPfloat((LPuint)1, out.m_data.exp);
		}
		return out;
	}
	MPfloat PiModule::MPfloatDiv(const MPfloat& mpf1, const MPfloat& mpf2, int n)
	{
		long double cs = (long double)mpf2.m_data.A[mpf2.m_data.len - 1];
		cs = 1 / cs;
		MPfloat re(cs, - (mpf2.m_data.len - 1));
		int nn = 1;
		MPfloat rnx;
		while (nn < n)
		{
			rnx = re * mpf2;
			if (rnx > MPfloat((LPuint)1))
			{
				re = re - (rnx - MPfloat((LPuint)1)) * re;
			}
			else
			{
				re = re + (MPfloat((LPuint)1) - rnx) * re;
			}
			re = MPfloatCut(re, n);
			nn *= 2;
		}
		return re * mpf1;
	}
}
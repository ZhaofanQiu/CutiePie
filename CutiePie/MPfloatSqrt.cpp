#include "stdafx.h"

#include "PiModule.h"

#include <string>

namespace PM
{
	void PiModule::MPfloatSqrt(MPfloat& res, const MPfloat& mpf, int n)
	{
		long double cs = (long double)mpf.m_data.A[mpf.m_data.len - 1];
		if (((mpf.m_data.len - 1) & 1) != 0)
		{
			cs = cs * exp2(64) + mpf.m_data.A[mpf.m_data.len - 2];
		}
		cs = 1 / sqrt(cs);
		MPfloat re(cs, -(int)floor((mpf.m_data.len - 1) / 2));
		int nn = 1;
		MPfloat rnx;
		while (nn < n)
		{
			rnx = re * re * mpf;
			
			if (rnx > MPfloat((LPuint)1))
			{
				re = re - (rnx - MPfloat((LPuint)1)) * MPfloat((LPuint)0x8000000000000000, -1) * re;
			}
			else
			{
				re = re + (MPfloat((LPuint)1) - rnx) * MPfloat((LPuint)0x8000000000000000, -1) * re;
			}
			re = MPfloatCut(re, n);
			nn <<= 1;
		}
		res = re;
	}
}
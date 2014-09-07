#include "stdafx.h"

#include "MultiPrecision.h"

using std::make_shared;

namespace MP
{
	MPfloat::MPfloat()
	{
		m_data = make_shared<struct _MPfloat>();
		m_data->len = 0;
		m_data->exp = 0;
	}

	MPfloat::MPfloat(const MPfloat& mpf)
	{
		m_data = mpf.m_data;
	}
	MPfloat::MPfloat(const LPuint* lpfs, int ls, int es)
	{
		m_data = make_shared<struct _MPfloat>();
		m_data->len = ls;
		m_data->exp = es;
		memcpy(m_data->A, lpfs, ls * sizeof(LPuint));
		while (m_data->A[m_data->len - 1] == 0)
			m_data->len--;
	}
	MPfloat::MPfloat(const LPuint lpf, int es)
	{
		m_data = make_shared<struct _MPfloat>();
		m_data->len = 1;
		m_data->exp = es;
		m_data->A[0] = lpf;
	}
	MPfloat::MPfloat(const MPuint& mpu, int bn)
	{
		m_data = make_shared<struct _MPfloat>();
		if (bn == -1 || bn > m_data->len)
		{
			m_data->len = mpu.m_data->len;
			m_data->exp = 0;
			memcpy(m_data->A, mpu.m_data->A, mpu.m_data->len * sizeof(LPuint));
		}
		else
		{
			m_data->len = bn;
			m_data->exp = mpu.m_data->len - bn;
			memcpy(m_data->A + m_data->len - bn, mpu.m_data->A + mpu.m_data->len - bn, bn * sizeof(LPuint));
		}
	}
	MPfloat::MPfloat(const long double df, int es)
	{
		m_data = make_shared<struct _MPfloat>();
		m_data->len = 2;
		int k = (int)floor(2 - log2(df) / 64);
		long double temp0 = df * exp2((long double)64 * (k - 1));
		long double temp1 = temp0;
		if (temp1 > (long double)0xffffffffffffefff)
			temp1 = (long double)0xffffffffffffefff;
		m_data->A[1] = (LPuint)(temp1);
		long double temp2 = df * exp2((long double)64 * k) - temp0 * exp2((long double)64);
		if (temp2 > (long double)0xffffffffffffefff)
			temp2 = (long double)0xffffffffffffefff;
		m_data->A[0] = (LPuint)(temp2);
		m_data->exp = es - k;
	}
	void MPfloat::Copy(const MPfloat& mpu)
	{
		m_data = make_shared<struct _MPfloat>();
		m_data->len = mpu.m_data->len;
		m_data->exp = mpu.m_data->exp;
		memcpy(m_data->A, mpu.m_data->A, m_data->len * sizeof(LPuint));
	}
}

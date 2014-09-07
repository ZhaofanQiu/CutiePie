#include "stdafx.h"

#include "MultiPrecision.h"

using std::make_shared;

namespace MP
{
	MPuint::MPuint()
	{
		m_data = make_shared<struct _MPuint>();
		m_data->len = 0;
	}

	MPuint::MPuint(const LPuint& lpu)
	{
		m_data = make_shared<struct _MPuint>();
		m_data->len = 1;
		m_data->A[0] = lpu;
	}

	MPuint::MPuint(const MPuint& mpu)
	{
		m_data = mpu.m_data;
	}

	MPuint::MPuint(const LPuint* lpus, int ls)
	{
		m_data = make_shared<struct _MPuint>();
		m_data->len = ls;
		memcpy(m_data->A, lpus, ls * sizeof(LPuint));
		while (m_data->A[m_data->len - 1] == 0)
		{
			m_data->len--;
		}
	}
	void MPuint::Cut(int bn)
	{
		if (bn >= m_data->len)
			return;
		shared_ptr<struct _MPuint> temp = make_shared<struct _MPuint>();
		temp->len = bn;
		memcpy(temp->A + temp->len - bn, m_data->A + m_data->len - bn, bn * sizeof(LPuint));
		m_data = temp;
	}
}

#include "stdafx.h"

#include "MultiPrecision.h"

using std::make_shared;

namespace MP
{
	MPuint::MPuint()
	{
		m_data.len = 0;
	}
	MPuint::MPuint(int ml)
	{
		m_data.A = new LPuint[ml];
		m_data._A = shared_ptr<LPuint>(m_data.A, [](LPuint* p){delete[] p; });
		m_data.len = 0;
	}

	MPuint::MPuint(const LPuint& lpu, int ml)
	{
		m_data.A = new LPuint[ml];
		m_data._A = shared_ptr<LPuint>(m_data.A, [](LPuint* p){delete[] p; });
		m_data.len = 1;
		m_data.A[0] = lpu;
	}

	MPuint::MPuint(const MPuint& mpu, int ml)
	{
		m_data = mpu.m_data;
	}

	MPuint::MPuint(const LPuint* lpus, int ls, int ml)
	{
		if (ml < ls)
			m_data.A = new LPuint[ls];
		else
			m_data.A = new LPuint[ml];
		m_data._A = shared_ptr<LPuint>(m_data.A, [](LPuint* p){delete[] p; });
		m_data.len = ls;
		memcpy(m_data.A, lpus, ls * sizeof(LPuint));
		while (m_data.A[m_data.len - 1] == 0)
		{
			m_data.len--;
		}
	}
	void MPuint::Cut(int bn)
	{
		if (bn >= m_data.len)
			return;
		struct _MPuint temp;
		temp.len = bn;
		temp.A = new LPuint[bn];
		temp._A = shared_ptr<LPuint>(m_data.A, [](LPuint* p){delete[] p; });

		memcpy(temp.A + temp.len - bn, m_data.A + m_data.len - bn, bn * sizeof(LPuint));
		m_data = temp;
	}
}

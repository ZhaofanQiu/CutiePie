#include "stdafx.h"

#include "PiModule.h"

#include <string>
#include <iostream>
using std::cout;
using std::endl;

namespace PM
{
	LPuint PiModule::MPfloatPos(MPfloat& mpf)
	{
		if (mpf.m_data->len > -mpf.m_data->exp)
		{
			mpf.m_data->len = -mpf.m_data->exp;
			return (mpf.m_data->A[mpf.m_data->len]);
		}
		else
			return 0;
	}
	void PiModule::MPfloatNPos(MPfloat& mpf)
	{
		if (mpf.m_data->exp <= 0 && mpf.m_data->len > -mpf.m_data->exp)
		{
			mpf.m_data->len = -mpf.m_data->exp;
		}
	}
	void PiModule::MPfloatPrint(const MPfloat& mpf, int n)
	{
		int k = 18;
		MPfloat temp;
		temp.Copy(mpf);
		MPfloatNPos(temp);
		
		char sout[19];
		while (n > k)
		{
			temp = temp * MPfloat((LPuint)1000000000000000000);
			LPuint pos = MPfloatPos(temp);
			sprintf_s(sout, 19, "%018I64u", pos);
			cout << sout;
			n = n - k;
		}
		temp = temp * MPfloat((LPuint)1000000000000000000);
		sprintf_s(sout, 19, "%018I64u", MPfloatPos(temp));
		char sout2[19];
		strncpy_s(sout2, sout, n);
		sout2[n] = '\0';
		cout << sout2 << endl;
	}
}
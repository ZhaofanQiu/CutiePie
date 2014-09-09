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
		if (mpf.m_data.len > -mpf.m_data.exp)
		{
			mpf.m_data.len = -mpf.m_data.exp;
			return (mpf.m_data.A[mpf.m_data.len]);
		}
		else
			return 0;
	}
	void PiModule::MPfloatNPos(MPfloat& mpf)
	{
		if (mpf.m_data.exp <= 0 && mpf.m_data.len > -mpf.m_data.exp)
		{
			mpf.m_data.len = -mpf.m_data.exp;
		}
	}
	void PiModule::MPfloatPrint(const MPfloat& mpf, int n)
	{
		int k = 18;
		MPfloat temp;
		temp.Copy(mpf);
		MPfloatNPos(temp);
		
		char sout[19];
		int i = 0;
		while (n > k)
		{
			temp = temp * (LPuint)1000000000000000000;
			LPuint pos = MPfloatPos(temp);
			sprintf_s(sout, 19, "%018I64u", pos);
			for (int j = 0; j < 18; j++)
			{
				if (i == 10)
				{
					cout << endl;
					i = 0;
				}
				cout << sout[j];
				i++;
			}
			n = n - k;
		}
		temp = temp * (LPuint)1000000000000000000;
		sprintf_s(sout, 19, "%018I64u", MPfloatPos(temp));
		for (int j = 0; j < n; j++)
		{
			if (i == 10)
			{
				cout << endl;
				i = 0;
			}
			i++;
			cout << sout[j];
		}
		cout << endl;
	}
}
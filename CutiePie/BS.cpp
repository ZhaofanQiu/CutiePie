#include "stdafx.h"

#include "PiModule.h"

#include <thread>

namespace PM
{
	void PiModule::BS(int a, int b, MPuint& P, MPuint& Q, MPuint& T, bool& flag)
	{
		if (b - a == 1)
		{
			if (a == 0)
			{
				P = MPuint((LPuint)1);
				Q = MPuint((LPuint)1);
			}
			else
			{
				P = MPuint((LPuint)(6 * a - 5));
				P = P * (LPuint)(2 * a - 1) * (LPuint)(6 * a - 1);
				Q = MPuint((LPuint)(a));
				Q = Q * a * a * 10939058860032000;
			}
			MPuint temp((LPuint)a);
			temp = temp * 545140134 + (LPuint)13591409;
			T = P * temp;
			if ((a & 1) != 0)
				flag = false;
			else
				flag = true;
		}
		else
		{
			int m = (LPuint)((a + b) / 2);
			MPuint Pam, Qam, Tam, Pmb, Qmb, Tmb;
			bool f1, f2;
			if (b - a >= 1024)
			{
				std::thread t1(BS, a, m, std::ref<MPuint>(Pam), std::ref<MPuint>(Qam), std::ref<MPuint>(Tam), std::ref<bool>(f1));
				std::thread t2(BS, m, b, std::ref<MPuint>(Pmb), std::ref<MPuint>(Qmb), std::ref<MPuint>(Tmb), std::ref<bool>(f2));
				t1.join();
				t2.join();
			}
			else
			{
				BS(a, m, Pam, Qam, Tam, f1);
				BS(m, b, Pmb, Qmb, Tmb, f2);
			}
			P = Pam * Pmb;
			Q = Qam * Qmb;
			//Tab = Qmb * Tam + Pam * Tmb;
			MPuint p1, p2;
			p1 = Qmb * Tam;
			p2 = Pam * Tmb;
			if (f1 && f2)
			{
				T = p1 + p2;
				flag = true;
			}
			else
			{
				if (f1 && !f2)
				{
					if (p1 > p2)
					{
						T = p1 - p2;
						flag = true;
					}
					else
					{
						T = p2 - p1;
						flag = false;
					}
				}
				else
				{
					if (!f1 && f2)
					{
						if (p1 > p2)
						{
							T = p1 - p2;
							flag = false;
						}
						else
						{
							T = p2 - p1;
							flag = true;
						}
						
					}
					else
					{
						if (!f1 && !f2)
						{
							T = p1 + p2;
							flag = false;
						}
					}
				}
			}
		}
	}
}
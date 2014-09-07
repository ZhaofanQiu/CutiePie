// CutiePie.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "PiModule.h"

int _tmain(int argc, _TCHAR* argv[])
{

	int k = 100000;

	LPuint cn = 10939058860032000;
	int dpt = (int)floor(log(cn / 6 / 2 / 6) / log(10));
	int N = int(k / dpt + 1);
	MP::MPfloat p, q, t;
	MP::MPuint _p, _q, _t;
	bool flag;
	PM::PiModule::BS(0, N, _p, _q, _t, flag);
	p = _p; q = _q;	t = _t;
	MP::MPfloat res((LPuint)4270934400);
	res = res * PM::PiModule::MPfloatSqrt(MPfloat((LPuint)10005), k) * PM::PiModule::MPfloatDiv(q, t, k);
	//PM::PiModule::MPfloatPrint(res, k);
}

// CutiePie.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "PiModule.h"

#include <thread>
#include <time.h>
#include <iostream>

int _tmain(int argc, _TCHAR* argv[])
{
	clock_t begin = clock();

	int k = 1000000;

	LPuint cn = 10939058860032000;
	int dpt = (int)floor(log(cn / 6 / 2 / 6) / log(10));
	int N = int(k / dpt + 1);
	MP::MPfloat p, q, t;
	MP::MPuint _p, _q, _t;
	bool flag;
	MP::MPfloat isq;
	std::thread t1(PM::PiModule::MPfloatSqrt, std::ref<MPfloat>(isq), MPfloat((LPuint)10005), k);

	PM::PiModule::BS(0, N, _p, _q, _t, flag);
	std::cout << "Finish BS, " << (double)(clock() - begin) / CLOCKS_PER_SEC << std::endl;
	p = _p; q = _q;	t = _t;
	MP::MPfloat res((LPuint)4270934400);
	res = PM::PiModule::MPfloatCut(res * PM::PiModule::MPfloatDiv(q, t, k), k);
	std::cout << "Finish div, " << (double)(clock() - begin) / CLOCKS_PER_SEC << std::endl;
	t1.join();
	res = PM::PiModule::MPfloatCut(res * isq, k);
	std::cout << "Finish calculate, " << (double)(clock() - begin) / CLOCKS_PER_SEC << std::endl;
	PM::PiModule::MPfloatPrint(res, k);
	std::cout << "Finish print, " << (double)(clock() - begin) / CLOCKS_PER_SEC << std::endl;
}


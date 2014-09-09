// CutiePie.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "PiModule.h"

#include <thread>
#include <time.h>
#include <iostream>

#include "complex.h"
#include "FFT.h"
std::vector<std::vector<complex>> twiddle_table;
int nk;

int _tmain(int argc, _TCHAR* argv[])
{
	if (argc != 2)
	{
		std::cout << "Usage: CutiePie.exe ndigits!" << std::endl;
		return 0;
	}

	clock_t begin = clock();
	bool debug = false;
	
	int k = _ttol(argv[1]);
	LPuint cn = 10939058860032000;
	int dpt = (int)floor(log(cn / 6 / 2 / 6) / log(10));
	int N = int(k / dpt + 1);
	MP::MPfloat p, q, t;
	MP::MPuint _p, _q, _t;
	bool flag;
	MP::MPfloat isq;

	std::thread t1(PM::PiModule::MPfloatSqrt, std::ref<MPfloat>(isq), MPfloat((LPuint)10005), k);

	PM::PiModule::BS(0, N, _p, _q, _t, flag);
	if (debug)
		std::cout << "Finish BS, " << (double)(clock() - begin) / CLOCKS_PER_SEC << std::endl;

	p = _p; q = _q;	t = _t;
	MP::MPfloat res((LPuint)4270934400);
	res = PM::PiModule::MPfloatCut(res * PM::PiModule::MPfloatDiv(q, t, k), k);
	if (debug)
		std::cout << "Finish div, " << (double)(clock() - begin) / CLOCKS_PER_SEC << std::endl;

	t1.join();
	res = PM::PiModule::MPfloatCut(res * isq, k);
	if (debug)
		std::cout << "Finish calculate, " << (double)(clock() - begin) / CLOCKS_PER_SEC << std::endl;
	
	if (!debug)
		PM::PiModule::MPfloatPrint(res, k);
	if (debug)
		std::cout << "Finish print, " << (double)(clock() - begin) / CLOCKS_PER_SEC << std::endl;
}


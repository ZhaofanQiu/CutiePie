#pragma once

#include "MultiPrecision.h"
using MP::MPfloat;
using MP::MPuint;

namespace PM
{
	class PiModule
	{
	public:
		static MPfloat MPfloatDiv(const MPfloat& mpf1, const MPfloat& mpf2, int n);
		static void MPfloatSqrt(MPfloat& res, const MPfloat& mpf, int n);
		static void BS(int a, int b, MPuint& P, MPuint& Q, MPuint& T, bool& flag);
		static void MPfloatPrint(const MPfloat& mpf, int n);
		static MPfloat MPfloatCut(const MPfloat& mpf, int n);
		static LPuint MPfloatPos(MPfloat& mpf);
		static void MPfloatNPos(MPfloat& mpf);
	};
}
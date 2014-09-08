#pragma once

#include "MultiPrecision.h"

namespace MP
{
	MPuint MpAdd(const MPuint& mpf1, const MPuint& mpf2, int exp);
	void MpMul(MPfloat& res, const MPfloat& mpf1, const MPfloat& mpf2);
	void MpMul2(MPuint& res, const MPuint& mpu1, const MPuint& mpu2);
}
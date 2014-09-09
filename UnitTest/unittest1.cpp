#include "stdafx.h"
#include "CppUnitTest.h"

#include "../CutiePie/MultiPrecision.h"
#include "../CutiePie/PiModule.h"
#include "../CutiePie/FFT.h"
#include <thread>
using namespace MP;
using namespace PM;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		TEST_METHOD(MPuintEqualTest)
		{
			LPuint d1[] = { 0, 0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff };
			LPuint d2[] = { 1, 1 };
			LPuint d3[] = { 1, 0, 0, 0, 1 };
			LPuint d4[] = { 0, 1, 0, 0, 1 };
			LPuint d5[] = { 0, 0, 0, 0, 1 };
			MPuint mpu1(d1, 4), mpu2(d2, 2), mpu3(d3, 5), mpu4(d4, 5), mpu5(d5, 5);
			Assert::IsTrue(mpu1 > mpu2);
			Assert::IsTrue(mpu2 < mpu3);
			Assert::IsTrue(mpu3 < mpu4);
			Assert::IsTrue(mpu4 > mpu5);
			Assert::IsTrue(mpu1 == mpu1);
		}
		TEST_METHOD(MPuintAddTest)
		{
			LPuint d1[] = { 0, 0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff };
			LPuint d2[] = { 1, 1 };
			LPuint d3[] = { 1, 0, 0, 0, 1 };
			LPuint d4[] = { 0, 1, 0, 0, 1 };
			LPuint d5[] = { 0, 0, 0, 0, 1 };
			MPuint mpu1(d1, 4), mpu2(d2, 2), mpu3(d3, 5), mpu4(d4, 5), mpu5(d5, 5);
			Assert::IsTrue(mpu3 == mpu1 + mpu2);
			Assert::IsTrue(mpu3 == mpu2 + mpu1);
			Assert::IsTrue(mpu4 == mpu3 + (LPuint)0xffffffffffffffff);
			Assert::IsTrue(mpu5 == mpu1 + (LPuint)0xffffffffffffffff + (LPuint)1);
		}
		TEST_METHOD(MPuintMulTest)
		{
			LPuint d1[] = { 0xfffffffffffffffd, 0x2, 0x3 };
			LPuint d2[] = { 0x3, 0xffe };
			LPuint d3[] = { 0xfffffffffffffff7, 0xffffffffffffd00e, 0x3002, 0x2ffa };
			LPuint d4[] = { 0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff };
			LPuint d5[] = { 0x2 };
			LPuint d6[] = { 0xfffffffffffffffe, 0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff, 1 };
			MPuint mpu1(d1, 3), mpu2(d2, 2), mpu3(d3, 4), mpu4(d4, 4), mpu5(d5, 1), mpu6(d6, 5);
			Assert::IsTrue(mpu3 == mpu1 * mpu2);
			Assert::IsTrue(mpu3 == mpu2 * mpu1);
			Assert::IsTrue(mpu6 == mpu4 * mpu5);
			Assert::IsTrue(mpu6 == mpu5 * mpu4);
			Assert::IsTrue(mpu6 == mpu4 * (LPuint)2);
		}
		TEST_METHOD(MPuintSubTest)
		{
			LPuint d1[] = { 0, 0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff };
			LPuint d2[] = { 1, 1 };
			LPuint d3[] = { 1, 0, 0, 0, 1 };
			LPuint d4[] = { 0, 1, 0, 0, 1 };
			LPuint d5[] = { 0, 0, 0, 0, 1 };
			MPuint mpu1(d1, 4), mpu2(d2, 2), mpu3(d3, 5), mpu4(d4, 5), mpu5(d5, 5);
			Assert::IsTrue(mpu3 - mpu1 == mpu2);
			Assert::IsTrue(mpu3 - mpu2 == mpu1);
			Assert::IsTrue(mpu4 - mpu3 == (LPuint)0xffffffffffffffff);
			Assert::IsTrue(mpu5 - (LPuint)0xffffffffffffffff == mpu1 + (LPuint)1);
		}
		TEST_METHOD(MPfloatEqualTest)
		{
			LPuint d1[] = { 0, 0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff };
			LPuint d2[] = { 0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff };
			LPuint d3[] = { 0, 0, 0, 0, 1 };
			LPuint d4[] = { 2 };
			MPfloat upf1(d1, 4, 0), upf2(d2, 3, 1),
				upf3(d1, 4, -1), upf4(d2, 3, 1),
				upf5(d3, 5, -1), upf6(d3, 5, 0), upf7((LPuint)2), upf8(d4, 1, 0);
			Assert::IsTrue(upf1 == upf2);
			Assert::IsTrue(upf1 != upf3);
			Assert::IsTrue(upf1 == upf4);
			Assert::IsTrue(upf1 > upf3);
			Assert::IsTrue(upf5 < upf1);
			Assert::IsTrue(upf6 > upf1);
			Assert::IsTrue(upf7 == upf8);
		}
		TEST_METHOD(MPfloatAddTest)
		{
			LPuint d1[] = { 0, 0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff };
			LPuint d2[] = { 1 };
			LPuint d3[] = { 1, 0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff };
			LPuint d4[] = { 0, 0, 0, 0, 1 };
			LPuint d5[] = { 0, 0xffffffffffffffff, 0, 0, 1 };
			LPuint d6[] = { 0, 0, 0, 1 };
			MPfloat mpf1(d1, 4, 0),	mpf2(d2, 1, 0),	mpf3(d3, 4, 0),	mpf4(d4, 5, 0),	
				mpf5(d5, 5, 0),	mpf6(d2, 1, 1),	mpf7(d1, 4, -1), mpf8(d6, 4, 0), mpf9(d2, 1, 2);
			Assert::IsTrue(mpf1 + mpf2 == mpf3);
			Assert::IsTrue(mpf1 + mpf9 == mpf5);
			Assert::IsTrue(mpf1 + mpf6 == mpf4);
			Assert::IsTrue(mpf7 + mpf2 == mpf8);
		}
		TEST_METHOD(MPfloatSubTest)
		{
			LPuint d1[] = { 0, 0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff };
			LPuint d2[] = { 1 };
			LPuint d3[] = { 1, 0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff };
			LPuint d4[] = { 0, 0, 0, 0, 1 };
			LPuint d5[] = { 0, 0xffffffffffffffff, 0, 0, 1 };
			LPuint d6[] = { 0, 0, 0, 1 };
			MPfloat mpf1(d1, 4, 0), mpf2(d2, 1, 0), mpf3(d3, 4, 0), mpf4(d4, 5, 0),
				mpf5(d5, 5, 0), mpf6(d2, 1, 1), mpf7(d1, 4, -1), mpf8(d6, 4, 0), mpf9(d2, 1, 2);
			Assert::IsTrue(mpf1 == mpf3 - mpf2);
			Assert::IsTrue(mpf1 == mpf5 - mpf9);
			Assert::IsTrue(mpf1 == mpf4 - mpf6);
			Assert::IsTrue(mpf7 == mpf8 - mpf2);
		}
		TEST_METHOD(MPfloatMulTest)
		{
			LPuint d1[] = { 0xfffffffffffffffd, 0x2, 0x3 };
			LPuint d2[] = { 0x3, 0xffe };
			LPuint d3[] = { 0xfffffffffffffff7, 0xffffffffffffd00e, 0x3002, 0x2ffa };
			LPuint d4[] = { 0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff };
			LPuint d5[] = { 0x2 };
			LPuint d6[] = { 0xfffffffffffffffe, 0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff, 1 };
			MPfloat mpf1(d1, 3, 100), mpf2(d2, 2, 50), mpf3(d3, 4, 150), mpf4(d4, 4, -10), mpf5(d5, 1, 0), mpf6(d6, 5, -10);
			Assert::IsTrue(mpf3 == mpf1 * mpf2);
			Assert::IsTrue(mpf3 == mpf2 * mpf1);
			Assert::IsTrue(mpf6 == mpf4 * mpf5);
			Assert::IsTrue(mpf6 == mpf5 * mpf4);
			Assert::IsTrue(mpf6 == mpf4 * (LPuint)2);
		}
		TEST_METHOD(MPfloatDivTest)
		{
			LPuint d1[] = { 0, 1 };
			LPuint d2[] = { 0x8000000000000000 };
			LPuint d3[] = { 0x8000000000000000, 0x8000000000000000, 0x8000000000000000 };
			LPuint d4[] = { 0x4000000000000000, 0x4000000000000000, 0x4000000000000000 };
			MPfloat mpf1(d1, 2, 0), mpf2(d2, 1, 0), mpf3(d3, 3, 0), mpf4(d4, 3, 0);
			Assert::IsTrue(PiModule::MPfloatDiv(mpf1, MPfloat((LPuint)2), 100) == mpf2);
			Assert::IsTrue(PiModule::MPfloatDiv(mpf1, mpf2, 100) == MPfloat((LPuint)2));
			Assert::IsTrue(PiModule::MPfloatDiv(mpf3, mpf4, 100) == MPfloat((LPuint)2));
		}
		TEST_METHOD(BSTest)
		{
			int k = 10000;
			LPuint cn = 10939058860032000;
			int dpt = (int)floor(log(cn / 6 / 2 / 6) / log(10));
			int N = int(k / dpt + 1);
			MP::MPuint _p, _q, _t;
			bool flag;
			PM::PiModule::BS(0, N, _p, _q, _t, flag);
		}
		TEST_METHOD(SqrtTest)
		{
			int k = 10000;
			MP::MPfloat isq;
			PM::PiModule::MPfloatSqrt(isq, MPfloat((LPuint)10005), k);
		}
		TEST_METHOD(MainTest)
		{
			int k = 10000;
			LPuint cn = 10939058860032000;
			int dpt = (int)floor(log(cn / 6 / 2 / 6) / log(10));
			int N = int(k / dpt + 1);
			MP::MPfloat p, q, t;
			MP::MPuint _p, _q, _t;
			bool flag;
			MP::MPfloat isq;
			std::thread t1(PM::PiModule::MPfloatSqrt, std::ref<MPfloat>(isq), MPfloat((LPuint)10005), k);

			PM::PiModule::BS(0, N, _p, _q, _t, flag);
			p = _p; q = _q;	t = _t;
			MP::MPfloat res((LPuint)4270934400);
			res = res * PM::PiModule::MPfloatDiv(q, t, k);
			t1.join();
			res = res * isq;
		}
	};
}
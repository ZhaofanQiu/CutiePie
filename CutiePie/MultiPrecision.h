#pragma once

#include <string>

#include <memory>
using std::shared_ptr;

#define MAX_P 32768

#define LPuint unsigned __int64
#define Suint std::string

struct _MPuint
{
	int len;
	LPuint A[MAX_P];
};

struct _MPfloat
{
	int len;
	int exp;
	LPuint A[MAX_P];
};

namespace MP
{
	class MPuint 
	{
	public:
		MPuint();
		MPuint(const LPuint& lpu);
		MPuint(const MPuint& mpu);
		MPuint(const LPuint* lpus, int ls);

		void Cut(int n);
		
		MPuint operator+(const MPuint& mpu);
		MPuint operator+(const LPuint& lpu);

		MPuint operator-(const MPuint& mpu);
		MPuint operator-(const LPuint& lpu);

		MPuint operator*(const MPuint& mpu);
		MPuint operator*(const LPuint& lpu);

		bool operator>(const MPuint& mpu) const;
		bool operator>(const LPuint& lpu) const;
		bool operator<(const MPuint& mpu) const;
		bool operator<(const LPuint& lpu) const;
		bool operator!=(const MPuint& mpu) const;
		bool operator!=(const LPuint& lpu) const;
		bool operator==(const MPuint& mpu) const;
		bool operator==(const LPuint& lpu) const;
		shared_ptr<struct _MPuint> m_data;
	};
	
	class MPfloat
	{
	public:
		MPfloat();
		MPfloat(const MPfloat& mpf);
		MPfloat(const LPuint* lpfs, int ls, int es);
		MPfloat(const LPuint lpf, int es = 0);
		MPfloat(const long double df, int es = 0);
		MPfloat(const MPuint& mpu, int bn = -1);
		void Copy(const MPfloat& mpu);
		MPfloat operator+(const MPfloat& mpf);

		MPfloat operator-(const MPfloat& mpf);

		MPfloat operator*(const MPfloat& mpf);
		MPfloat operator*(const LPuint& lpf);

		bool operator>(const MPfloat& mpf) const;
		bool operator<(const MPfloat& mpf) const;
		bool operator!=(const MPfloat& mpf) const;
		bool operator==(const MPfloat& mpf) const;

		shared_ptr<struct _MPfloat> m_data;
	};
}
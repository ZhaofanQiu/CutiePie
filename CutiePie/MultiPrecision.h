#pragma once

#include <string>

#include <memory>
using std::shared_ptr;

#define LPuint unsigned __int64
#define Suint std::string

struct _MPuint
{
	int len;
	LPuint* A;
	shared_ptr<LPuint> _A;
};

struct _MPfloat
{
	int len;
	int exp;
	LPuint* A;
	shared_ptr<LPuint> _A;
};

namespace MP
{
	class MPuint 
	{
	public:
		MPuint();
		MPuint(int ml);
		MPuint(const LPuint& lpu, int ml = 1);
		MPuint(const MPuint& mpu, int ml);
		MPuint(const LPuint* lpus, int ls, int ml = -1);

		void Cut(int n);
		
		MPuint operator+(const MPuint& mpu) const;
		MPuint operator+(const LPuint& lpu) const;

		MPuint operator-(const MPuint& mpu) const;
		MPuint operator-(const LPuint& lpu) const;

		MPuint operator*(const MPuint& mpu) const;
		MPuint operator*(const LPuint& lpu) const;

		bool operator>(const MPuint& mpu) const;
		bool operator>(const LPuint& lpu) const;
		bool operator<(const MPuint& mpu) const;
		bool operator<(const LPuint& lpu) const;
		bool operator!=(const MPuint& mpu) const;
		bool operator!=(const LPuint& lpu) const;
		bool operator==(const MPuint& mpu) const;
		bool operator==(const LPuint& lpu) const;
		struct _MPuint m_data;
	};
	
	class MPfloat
	{
	public:
		MPfloat();
		MPfloat(int ml);
		MPfloat(const MPfloat& mpf, int ml);
		MPfloat(const LPuint* lpfs, int ls, int es, int ml = -1);
		MPfloat(const LPuint lpf, int es = 0, int ml = 1);
		MPfloat(const long double df, int es = 0, int ml = 2);
		MPfloat(const MPuint& mpu, int bn = -1);
		void Copy(const MPfloat& mpu);
		MPfloat operator+(const MPfloat& mpf)const;

		MPfloat operator-(const MPfloat& mpf)const;

		MPfloat operator*(const MPfloat& mpf)const;
		MPfloat operator*(const LPuint& lpf)const;

		bool operator>(const MPfloat& mpf) const;
		bool operator<(const MPfloat& mpf) const;
		bool operator!=(const MPfloat& mpf) const;
		bool operator==(const MPfloat& mpf) const;

		struct _MPfloat m_data;
	};
}
#pragma once

#define MAX_P 10000
#define LPuint unsigned __int64

namespace MP
{
	class MPuint
	{
	public:
		MPuint();
		MPuint(LPuint lpu);
		MPuint(MPuint& mpu);

		MPuint operator=(MPuint& mpu);

		MPuint operator+(MPuint& mpu);
		MPuint operator+(LPuint& lpu);

		MPuint operator*(MPuint& mpu);
		MPuint operator*(LPuint& lpu);

		MPuint operator>(MPuint& mpu);
		MPuint operator>(LPuint& lpu);

		MPuint operator==(MPuint& mpu);
		MPuint operator==(LPuint& lpu);


	private:
		int m_length;
		LPuint m_A[MAX_P];
	};
}
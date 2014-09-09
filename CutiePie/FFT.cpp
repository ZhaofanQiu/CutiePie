#include "stdafx.h"

#include "FFT.h"
#include <thread>

#define M_PI 3.14159265358979323846
extern std::vector<std::vector<complex>> twiddle_table;
extern int nk;

namespace FFT
{
	void fft_forward(__m128d *T,int k, int kk)
	{ 
		if (k == 1){
			__m128d a = T[0];
			__m128d b = T[1];
			T[0] = _mm_add_pd(a, b);
			T[1] = _mm_sub_pd(a, b);
			return;
		}
		size_t length = 1 << k;
		size_t half_length = length / 2;
		std::vector<complex> &local_table = twiddle_table[k];
		for (size_t c = 0; c < half_length; c++){
			__m128d r0 = _mm_loaddup_pd(&local_table[c].r);
			__m128d i0 = _mm_loaddup_pd(&local_table[c].i);
			__m128d a0 = T[c];
			__m128d b0 = T[c + half_length];
			__m128d c0, d0;
			c0 = _mm_add_pd(a0, b0);
			d0 = _mm_sub_pd(a0, b0);
			T[c] = c0;
			c0 = _mm_mul_pd(d0, r0);
			d0 = _mm_mul_pd(_mm_shuffle_pd(d0, d0, 1), i0);
			c0 = _mm_addsub_pd(c0, d0);
			T[c + half_length] = c0;
		}
		if (k >= kk - 1)
		{
			std::thread t1(fft_forward, T, k - 1, kk);
			std::thread t2(fft_forward, T + half_length, k - 1, kk);
			t1.join();
			t2.join();
		}
		else
		{
			fft_forward(T, k - 1, kk);
			fft_forward(T + half_length, k - 1, kk);
		}
	} 
	void fft_inverse(__m128d *T,int k, int kk)
	{ 
		if (k == 1){
			__m128d a = T[0];
			__m128d b = T[1];
			T[0] = _mm_add_pd(a, b);
			T[1] = _mm_sub_pd(a, b);
			return;
		}
		size_t length = 1 << k;
		size_t half_length = length / 2;
		if (k >= kk - 1)
		{
			std::thread t1(fft_inverse, T, k - 1, kk);
			std::thread t2(fft_inverse, T + half_length, k - 1, kk);
			t1.join();
			t2.join();
		}
		else
		{
			fft_inverse(T, k - 1, kk);
			fft_inverse(T + half_length, k - 1, kk);

		}

		std::vector<complex> &local_table = twiddle_table[k];
		for (size_t c = 0; c < half_length; c++){
			__m128d r0 = _mm_loaddup_pd(&local_table[c].r);
			__m128d i0 = _mm_loaddup_pd(&local_table[c].i);
			i0 = _mm_xor_pd(i0, _mm_set1_pd(-0.0));
			__m128d a0 = T[c];
			__m128d b0 = T[c + half_length];
			__m128d c0, d0;
			c0 = _mm_mul_pd(b0, r0);
			d0 = _mm_mul_pd(_mm_shuffle_pd(b0, b0, 1), i0);
			c0 = _mm_addsub_pd(c0, d0);
			b0 = _mm_add_pd(a0, c0);
			d0 = _mm_sub_pd(a0, c0);
			T[c] = b0;
			T[c + half_length] = d0;
		}
	}

	void fft_pointwise(__m128d *T,__m128d *A,int k)
	{ 
		size_t length = 1 << k;
		for (size_t c = 0; c < length; c++){
			__m128d a0 = T[c];
			__m128d b0 = A[c];
			__m128d c0, d0;
			c0 = _mm_mul_pd(a0, _mm_unpacklo_pd(b0, b0));
			d0 = _mm_mul_pd(_mm_shuffle_pd(a0, a0, 1), _mm_unpackhi_pd(b0, b0));
			T[c] = _mm_addsub_pd(c0, d0);
		}
	}

	void int_to_fft(__m128d *T, int k, const unsigned __int64 *A, size_t AL)
	{
		size_t fft_length = 1 << k;
		__m128d *Tstop = T + fft_length;
		if (fft_length < 8 * AL)
			throw "FFT length is too small.";
		for (size_t c = 0; c < AL; c++){
			unsigned __int64 word = A[c];
			*T++ = _mm_set_sd(word & 0xff);
			word >>= 8;
			*T++ = _mm_set_sd(word & 0xff);
			word >>= 8;
			*T++ = _mm_set_sd(word & 0xff);
			word >>= 8;
			*T++ = _mm_set_sd(word & 0xff);
			word >>= 8;
			*T++ = _mm_set_sd(word & 0xff);
			word >>= 8;
			*T++ = _mm_set_sd(word & 0xff);
			word >>= 8;
			*T++ = _mm_set_sd(word & 0xff);
			word >>= 8;
			*T++ = _mm_set_sd(word);
		}
		while (T < Tstop)
			*T++ = _mm_setzero_pd();
	}

	void fft_to_int(__m128d *T, int k, unsigned __int64 *A, size_t AL)
	{
		size_t fft_length = 1 << k;
		double scale = 1. / fft_length;
		if (fft_length < 8 * AL)
			throw "FFT length is too small.";
		unsigned __int64 carry = 0;
		for (size_t c = 0; c < AL; c++){
			double   f_point;
			unsigned __int64 i_point;
			unsigned __int64 word;

			f_point = ((double*)T++)[0] * scale;    //  Load and scale 
			i_point = (unsigned __int64)(f_point + 0.5);    //  Round 
			carry += i_point;                       //  Add to carry 
			word = carry & 0xff;                    //  Get 3 digits. 
			carry >>= 8;

			f_point = ((double*)T++)[0] * scale;    //  Load and scale 
			i_point = (unsigned __int64)(f_point + 0.5);    //  Round 
			carry += i_point;                       //  Add to carry 
			word += (carry & 0xff) << 8;          //  Get 3 digits. 
			carry >>= 8;

			f_point = ((double*)T++)[0] * scale;    //  Load and scale 
			i_point = (unsigned __int64)(f_point + 0.5);    //  Round 
			carry += i_point;                       //  Add to carry 
			word += (carry & 0xff) << 16;       //  Get 3 digits. 
			carry >>= 8;

			f_point = ((double*)T++)[0] * scale;    //  Load and scale 
			i_point = (unsigned __int64)(f_point + 0.5);    //  Round 
			carry += i_point;                       //  Add to carry 
			word += (carry & 0xff) << 24;       //  Get 3 digits. 
			carry >>= 8;

			f_point = ((double*)T++)[0] * scale;    //  Load and scale 
			i_point = (unsigned __int64)(f_point + 0.5);    //  Round 
			carry += i_point;                       //  Add to carry 
			word += (carry & 0xff) << 32;       //  Get 3 digits. 
			carry >>= 8;

			f_point = ((double*)T++)[0] * scale;    //  Load and scale 
			i_point = (unsigned __int64)(f_point + 0.5);    //  Round 
			carry += i_point;                       //  Add to carry 
			word += (carry & 0xff) << 40;       //  Get 3 digits. 
			carry >>= 8;

			f_point = ((double*)T++)[0] * scale;    //  Load and scale 
			i_point = (unsigned __int64)(f_point + 0.5);    //  Round 
			carry += i_point;                       //  Add to carry 
			word += (carry & 0xff) << 48;       //  Get 3 digits. 
			carry >>= 8;

			f_point = ((double*)T++)[0] * scale;    //  Load and scale 
			i_point = (unsigned __int64)(f_point + 0.5);    //  Round 
			carry += i_point;                       //  Add to carry 
			word += (carry & 0xff) << 56;       //  Get 3 digits. 
			carry >>= 8;

			A[c] = word;
		}
	}

	void fft_init(int k)
	{
		int current_k = (int)twiddle_table.size() - 1;
		if (current_k >= k)
			return;
		if (k - 1 > current_k){
			fft_init(k - 1);
		}
		size_t length = 1 << k;
		double omega = 2 * M_PI / length;
		length /= 2;
		std::vector<complex> sub_table;
		for (size_t c = 0; c < length; c++){
			double angle = omega * c;
			auto twiddle_factor = complex(cos(angle), sin(angle));
			sub_table.push_back(twiddle_factor);
		}
		twiddle_table.push_back(std::move(sub_table));
	}
}

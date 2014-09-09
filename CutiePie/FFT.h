#pragma once

#include "complex.h"

namespace FFT
{
	void fft_forward(__m128d *T, int k, int kk);
	void fft_inverse(__m128d *T, int k, int kk);
	void fft_pointwise(__m128d *T, __m128d *A, int k);
	void int_to_fft(__m128d *T, int k, const unsigned __int64 *A, size_t AL);
	void fft_to_int(__m128d *T, int k, unsigned __int64 *A, size_t AL);
	void fft_init(int k);
}
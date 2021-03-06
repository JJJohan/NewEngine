#pragma once

#include <emmintrin.h>

namespace Engine
{
	namespace Math
	{
		const float Pi = 3.14159265358979323846f;

		inline float Min(float a, float b)
		{
			// Branchless SSE min.
			_mm_store_ss(&a, _mm_min_ss(_mm_set_ss(a), _mm_set_ss(b)));
			return a;
		}

		inline float Max(float a, float b)
		{
			// Branchless SSE max.
			_mm_store_ss(&a, _mm_max_ss(_mm_set_ss(a), _mm_set_ss(b)));
			return a;
		}

		inline float Clamp(float val, float minval, float maxval)
		{
			// Branchless SSE clamp.
			// return minss( maxss(val,minval), maxval );

			_mm_store_ss(&val, _mm_min_ss(_mm_max_ss(_mm_set_ss(val), _mm_set_ss(minval)), _mm_set_ss(maxval)));
			return val;
		}
	}
}

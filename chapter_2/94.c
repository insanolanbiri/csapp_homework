#include <assert.h>
#include <limits.h>
#include <math.h>

#include "bit_level_float.h"

float_bits float_twice(float_bits f)
{
	unsigned sign = f >> 31;
	unsigned exp = f >> 23 & 0xFF;
	unsigned frac = f & 0x7FFFFF;

	if (!(~exp << 24))	// exp is all ones
	{
		// NaN or inf, can simply return f
		return f;
	}

	if (!exp) {
		// denormalized
		if (!(frac >> 22)) {
			// msb of frac is not set, result is also denormalized
			frac = frac << 1;
		} else {
			// convert to normalized
			// bias = 127
			// previous E was 1-127, it'll be the same (new exp = 1)
			exp = 1;

			// frac will be simply shifted 1 bits to the left:
			frac = frac << 1;

		}
	} else {
		// normalized
		if (!((~(exp + 1)) << 24))	// exp is 11..110, just before inf
		{
			// result should be inf
			frac = 0;
		}
		// multiply by 2, this might result in inf
		exp += 1;
	}

	return sign << 31 | exp << 23 | (frac & 0x7FFFFF);
}

int main()
{
	float_bits i = 0;
	do {
		float number = *(float *)&i;
		float expected = 2 * number;
		float_bits expected_bits = *(float_bits *) & expected;
		float_bits homemade_bits = float_twice(i);

		if (isnan(number)) {
			assert(homemade_bits == i);
		} else {
			assert(homemade_bits == expected_bits);
		}

	}
	while (i++ != UINT_MAX);
	return 0;
}

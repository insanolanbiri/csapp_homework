#include <math.h>
#include <assert.h>
#include <limits.h>

#include "bit_level_float.h"

float_bits float_half(float_bits f)
{
	unsigned sign = f >> 31;
	unsigned exp = f >> 23 & 0xFF;
	unsigned frac = f & 0x7FFFFF;

	if (exp == 0xFF)	// exp is all ones
	{
		// NaN or inf, can simply return f
		return f;
	}

	if (!exp) {
		// denormalized
		unsigned low_bit = frac & 0x1;
		frac = frac >> 1;
		if (low_bit && (frac & 0x1)) {
			// round to even
			frac += 1;
		}

	} else if (exp == 1) {
		unsigned low_bit = frac & 0x1;
		frac = frac >> 1;
		frac = frac | 0x400000;	// set msb to 1
		if (low_bit && (frac & 0x1)) {
			// round to even
			frac += 1;
		}

		exp = frac >> 23;	// 1 if overflowed, else 0

	} else {
		// exp is big enough to divide simply:
		exp -= 1;
	}
	return sign << 31 | exp << 23 | (frac & 0x7FFFFF);

}

int main()
{
	unsigned i = 0;
	do {
		float number = *(float *)(&i);
		float expected = number / 2.0;
		float_bits expected_bits = *(float_bits *) (&expected);
		float_bits homemade_bits = float_half(i);

		if (isnan(number)) {
			assert(homemade_bits == i);
		} else {
			assert(homemade_bits == expected_bits);
		}

	}
	while (i++ < UINT_MAX);
	return 0;
}

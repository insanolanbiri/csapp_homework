#include <assert.h>
#include <limits.h>

#include "bit_level_float.h"

#define FLOAT_BIAS 127

int leftmost_one(unsigned x);

float_bits float_i2f(int i)
{
	if (!i) {

		return 0;
	}

	int sign = i >> 31;	// 00..00 or 11..11
	unsigned u = (sign & (~i + 1)) | (~sign & i);	// abs value

	int shift = 31;
	for (; !(u >> shift); shift--) ;

	unsigned exp = shift + FLOAT_BIAS;

	unsigned frac = u << (31 - shift);	// 1.xyz

	unsigned low_bits = frac & 0xFF;
	unsigned low_bit = low_bits & 0x80;
	low_bits -= low_bit;

	frac >>= 8;

	if (low_bit) {

		if (low_bits) {
			frac += 1;
		} else {
			if (frac & 0x1)
				frac += 1;
		}

	}

	if (!((frac >> 23) & 0x1) && !(u >> 31)) {
		exp += 1;
		frac >>= 1;
	}

	frac &= 0x7FFFFF;

	return (sign << 31) | (exp << 23) | frac;
}

int main()
{
	for (int i = INT_MIN; i < INT_MAX; i++) {
		float expected = (float)i;
		float_bits expected_bits = *(float_bits *) (&expected);
		float_bits homemade_bits = float_i2f(i);

		assert(expected_bits == homemade_bits);

	}
	return 0;
}

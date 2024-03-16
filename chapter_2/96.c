#include <assert.h>
#include <limits.h>

#include "bit_level_float.h"

#define FLOAT_TO_INT_ERROR_FLAG 0x80000000
#define FLOAT_EXP_BIAS ((1 << (8-1)) -1)

int float_f2i(float_bits f)
{
	unsigned sign = f >> 31;
	unsigned exp = f >> 23 & 0xFF;
	unsigned frac = f & 0x7FFFFF;

	if (exp == 0xFF)	// all ones
	{
		// NaN or inf
		return FLOAT_TO_INT_ERROR_FLAG;
	}

	if (exp == 0) {
		// denorm values have an exponent value of -126, this is literally zero on integer domain
		return 0;
	}

	int E = (int)exp - FLOAT_EXP_BIAS;

	if (E < 0) {
		// 1.xyz shifted to the right by -E times
		return 0;
	}

	if (E > 30) {
		// if 1.xyz had been shifted to the left by 31 times, that'd be an 33 bit integer (there is also a negative weighted bit)
		return FLOAT_TO_INT_ERROR_FLAG;
	}

	int result = 0;

	// below line can also be implemented without casting to 64-bit, using a few if statements.
	result |= (unsigned long)frac << E >> 23;

	result |= 1 << E;	// the hidden bit of normalized numbers

	if (sign) {
		result *= -1;
	}

	return result;
}

int main()
{
	unsigned i = 0;
	do {
		float num = *(float *)&i;

		int expected = (int)num;
		int homemade = float_f2i(i);

		assert(expected == homemade);
	} while (i++ < UINT_MAX);
}

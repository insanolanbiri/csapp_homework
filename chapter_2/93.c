#include <assert.h>
#include <limits.h>
#include <math.h>

#include "bit_level_float.h"

float_bits float_absval(float_bits f)
{
	unsigned exp = f >> 23 & 0xFF;
	unsigned frac = f & 0x7FFFFF;

	if (!(~exp & 0xFF) && frac) {
		// NaN
		return f;
	}

	return f & (~0u >> 1);
}

int main()
{
	unsigned i = 0;
	do {

		float number = *(float *)(&i);
		float expected = fabs(number);
		if (isnan(number)) {
			assert(float_absval(i) == i);
		} else {
			assert(float_absval(i) == *(float_bits *) & expected);
		}
	} while (i++ < UINT_MAX);

	return 0;
}

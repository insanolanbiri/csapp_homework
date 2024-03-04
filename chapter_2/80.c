#include "divide_power2.h"

int threefourths(int x)
{
	int low = x & 0x03;

	int sign = (x >> ((sizeof(int) << 3) - 1));

	x = x & ~0x03;

	int high = divide_power2(x, 2);
	high = (high << 1) + high;	// multp by 3

	low = (low << 1) + low;
	low = (sign & low + 3) | (~sign & low);

	low = divide_power2(low, 2);

	return high + low;
}

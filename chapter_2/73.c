#include <limits.h>

int saturating_add(int x, int y)
{
	int sum = x + y;

	int int_sign_index = (sizeof(int) << 3) - 1;

	int x_sign_bit = x >> int_sign_index;
	int y_sign_bit = y >> int_sign_index;
	int sum_sign_bit = sum >> int_sign_index;

	// overflow has occured if and only if the sign bit of x is the same as y's, and not the same as sum's.
	int neg_over = x_sign_bit & y_sign_bit & !sum_sign_bit;	// 1 if neg overflow
	int pos_over = !x_sign_bit & !y_sign_bit & sum_sign_bit;	// 1 if pos overflow

	return (!(neg_over || pos_over) & sum) |
	    (!(!neg_over || pos_over) & INT_MIN) |
	    (!(neg_over || !pos_over) & INT_MAX);
}

int signed_high_prod(int x, int y);

unsigned unsigned_high_prod(unsigned x, unsigned y)
{
	int length = sizeof(unsigned) << 3;
	unsigned x_sign = x >> (length - 1);
	unsigned y_sign = y >> (length - 1);

	return signed_high_prod(x, y) + x_sign * y + y_sign * x;
}

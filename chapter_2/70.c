int fits_bits(int x, int n)
{
	int int_len = sizeof(int) << 3;
	int overflowed = x >> (int_len - n);
	return !overflowed || !~overflowed;
}

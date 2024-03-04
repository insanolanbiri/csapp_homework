int divide_power2(int x, int k)
{
	int sign = x >> ((sizeof(x) << 3) - 1);

	return (sign & ((x + (1 << k) - 1) >> k)) | (~sign & x >> k);
}

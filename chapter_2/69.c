unsigned rotate_left(unsigned x, int n)
{
	return x << n | (x >> (sizeof(x) - n - 1) >> 1);
}

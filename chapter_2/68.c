int lower_one_mask(int n)
{
	return (~0u) >> ((sizeof(int) << 8) - n);
}

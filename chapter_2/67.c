int int_size_is_32_B()
{
	int msb32 = 1 << 31;
	int postmsb32 = msb32 << 1;

	return msb32 && !postmsb32;
}

int int_size_is_32_C()
{

	int msb32 = 1 << 15 << 15 << 1;
	int postmsb32 = msb32 << 1;

	return msb32 && !postmsb32;
}

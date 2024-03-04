int mul3div4(int x)
{
	int mul = (x << 1) + x;
	int mul_sign = mul >> ((sizeof(int) << 3) - 1);

	return (mul_sign & (mul + 1) >> 1) | (~mul_sign & mul >> 1);
}

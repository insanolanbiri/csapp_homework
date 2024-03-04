/* Solutions for homework 2.61 */

// A.
int has_one(int x)
{
	return !(!x);
}

// B.
int has_zero(int x)
{
	return !!~x;
}

// C.
int has_one_in_lsb(int x)
{
	return !!(x << ((sizeof(x) - 1) << 3));
}

// D.
int has_zero_in_msb(int x)
{
	return !!((~x >> ((sizeof(x) - 1) << 3)) & 0xFF);
}

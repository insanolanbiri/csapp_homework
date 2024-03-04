typedef unsigned packed_t;

int xbyte(packed_t word, int bytenum)
{
	int a = (word >> (bytenum << 3));
	return (a << 24) >> 24;

	/* alternative solution (from https://github.com/xr1s/CSAPP):
	 * return (int) word << (3 - bytenum << 3) >> 24;
	 */
}

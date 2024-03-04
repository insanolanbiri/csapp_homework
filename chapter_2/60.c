#include <stdio.h>

unsigned replace_byte(unsigned x, int i, unsigned char b)
{
	unsigned incoming = ~(~x | (0xFF << 8 * i));
	unsigned new = (unsigned)b << 8 * i;

	return incoming | new;
}

int main()
{
	unsigned x = 0x12345678;
	unsigned char new = 0xAB;

	for (int i = 0; i < 4; i++) {
		unsigned value = replace_byte(x, i, new);
		printf("x = %x, i = %d, b = %x; value = %x\n", x, i, new,
		       value);
	}
	return 0;
}

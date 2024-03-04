#include <stdio.h>

/* Perform shift logically */
unsigned srl(unsigned x, int k)
{
	/* Perform shift arithmetically */
	unsigned xsra = (int)x >> k;
	return xsra & ~(~(0u) << (8 * sizeof(int) - k - 1) << 1);
}

/* Perform shift arithmetically */
int sra(int x, int k)
{
	/* Perform shift logically */
	int xsrl = (unsigned)x >> k;
	// last (8*sizeof(int)-k)) bits
	int sign_bit = !!(x & (~(0u) << (8 * sizeof(int) - 1)));
	int mask = ((0 - sign_bit) << (8 * sizeof(int) - k - 1) << 1);

	return xsrl | mask;
}

int main()
{
	for (int i = -1024; i <= 1024; i = i + 256) {
		for (int k = 0; k < 5; k++) {
			printf("sra(%d,%d) is %d\n", i, k, sra(i, k));
			printf("srl(%d,%d) is %d\n", i, k, srl(i, k));
		}
		printf("\n");
	}

	return 0;
}

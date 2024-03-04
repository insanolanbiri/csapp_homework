#include <stdio.h>
#include <stdlib.h>

// yield a word consisting of the least significant byte of x and the remaining bytes of y
int fuse_words(int x, int y)
{
	return x & 0xFF | y & (~0xFF);
}

int main(int argc, char **argv)
{
	int x = 0x89ABCDEF, y = 0x76543210;

	if (argc == 3) {
		x = strtol(argv[1], NULL, 0);
		y = strtol(argv[2], NULL, 0);
	}

	int result = fuse_words(x, y);

	printf("result: %d (0x%x)\n", result, result);

	return 0;
}

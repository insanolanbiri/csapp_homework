#include <stdio.h>

int is_little_endian()
{
	int a = 1;
	if (*(unsigned char *)(&a) == 1) {
		return 1;
	}
	return 0;
}

int main()
{
	printf("is_little_endian() returned %d\n", is_little_endian());
	return 0;
}

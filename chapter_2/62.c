#include <stdio.h>

int int_shifts_are_arithmetic()
{
	int a = 0;
	a = ~a;
	return (a >> 1) == a;
}

int main()
{
	printf("int_shifts_are_artithmetic() returned %d\n",
	       int_shifts_are_arithmetic());

	return 0;
}

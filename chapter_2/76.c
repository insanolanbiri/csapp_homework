#include <stdlib.h>
#include <string.h>

void *calloc(size_t nmemb, size_t size)
{
	size_t total_length = nmemb * size;
	if (total_length == 0) {
		return NULL;
	}

	if (total_length / nmemb != size) {
		// multiplication overflow
		return NULL;
	}

	void *ptr = malloc(total_length);

	if (ptr == NULL) {
		return NULL;
	}

	memset(ptr, 0x0, total_length);

	return ptr;
}

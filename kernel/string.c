#include <stdbool.h>
#include <stddef.h>
#include <stdarg.h>
#include <string.h>

/*
 * memset
 *
 * Set num bytes starting at ptr to value.
 */
void *memset(void *ptr, int value, size_t num)
{
	char *bytes = ptr;
	for (size_t i = 0; i < num; i++) {
		bytes[i] = value;
	}
	return ptr;
}

/*
 * memcpy
 *
 * Copy num bytes from source into the contiguous span of memory starting
 * at destination.
 */
void *memcpy(void *destination, const void *source, size_t num)
{
	char *dest = destination;
	const char *src = source;
	for (size_t i = 0; i < num; i++) {
		dest[i] = src[i];
	}
	return destination;
}

/*
 * strlen
 *
 * Computer the number of characters in a string starting at str
 * and going util the first null character. Return the number of
 * characters.
 */
size_t strlen(const char *str)
{
	size_t ret = 0;
	while (str[ret] != '\0')
		ret++;
	return ret;
}

/*
 * strcpy
 *
 * Copy characters in source to destination until the first null
 * character in source is encountered.
 */
char *strcpy(char *destination, const char *source)
{
	memcpy(destination, source, strlen(source));
	return destination;
}


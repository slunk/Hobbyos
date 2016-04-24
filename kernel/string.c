#include <stdbool.h>
#include <stddef.h>
#include <stdarg.h>
#include <string.h>

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


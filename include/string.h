#ifndef _STRING_H
#define _STRING_H
#include <stdbool.h>
#include <stddef.h>
#include <stdarg.h>

size_t strlen(const char *str);
char *strcpy(char *destination, const char *source);
void *memset(void *ptr, int value, size_t num);
void *memcpy(void *destination, const void *source, size_t num);
#endif

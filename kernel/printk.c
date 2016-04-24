#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <display.h>
#include <printk.h>
#include <system.h>

/*
 * chr
 *
 * Convert a single decimal digit to its ASCII character code.
 */
char chr(uint8_t value)
{
	return ((uint8_t) '0') + value;
}

/*
 * itoa
 *
 * Convert an integer value to a string in the number system specified
 * by base and store the string representation of value in str.
 */
char *itoa(uint32_t value, char *str, int base)
{
	int num_digits = 0;
	int tmp;
	if (value == 0) {
		str[0] = chr(0);
		return str;
	}
	for (tmp = value; tmp != 0; tmp /= base) {
		num_digits++;
	}
	tmp = value;
	for (int i = 0; i < num_digits; i++) {
		if (tmp % base < 10) {
			str[num_digits - i - 1] = chr(tmp % base);
		} else {
			str[num_digits - i - 1] = 'A' + (tmp % base) - 10;
		}
		tmp /= base;
	}
	return str;
}

/*
 * printk
 *
 * Print a format string to the terminal with special character sequences
 * replaced by arguments.
 *
 * Currently supported format char sequences: %c, %s, %d, %x.
 *
 * TODO: Implement complete printk functionality.
 */
void printk(const char *fmt, ...)
{
	va_list ap;
	uint8_t fmtln = strlen(fmt);
	char numstr[32] = {0};
	memset(numstr, 0, 32);
	va_start(ap, fmt);
	for (uint8_t i = 0; i < fmtln; i++) {
		if (fmt[i] != '%') {
			terminal_putchar(fmt[i]);
		} else {
			switch (fmt[++i]) {
			case 'c':
				terminal_putchar((char) va_arg(ap, int));
				break;
			case 's':
				terminal_writestring(va_arg(ap, char *));
				break;
			case 'd':
				terminal_writestring(itoa(va_arg(ap, int), numstr, 10));
				memset(numstr, 0, 32);
				break;
			case 'x':
				terminal_writestring(itoa(va_arg(ap, int), numstr, 16));
				memset(numstr, 0, 32);
				break;
			default:
				//TODO: Panic
				break;
			}
		}
	}
	va_end(ap);
}

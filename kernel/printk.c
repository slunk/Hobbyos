#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <display.h>
#include <printk.h>

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
char *itoa(uint8_t value, char *str, uint8_t base)
{
	uint8_t num_digits = 0;
	uint8_t tmp;
	if (value == 0) {
		str[0] = chr(0);
		return str;
	}
	for (tmp = value; tmp != 0; tmp /= base) {
		num_digits++;
	}
	tmp = value;
	for (uint8_t i = 0; i < num_digits; i++) {
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
	char numstr[5] = {0};
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
				memset(numstr, 0, 5);
				break;
			case 'x':
				terminal_writestring(itoa(va_arg(ap, int), numstr, 16));
				memset(numstr, 0, 5);
				break;
			default:
				//TODO: Panic
				break;
			}
		}
	}
	va_end(ap);
}

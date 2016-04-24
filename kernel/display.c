#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>
#include <system.h>
#include <string.h>
#include <display.h>

uint8_t make_color(enum vga_color fg, enum vga_color bg)
{
	return fg | bg << 4;
}

uint16_t make_vgaentry(char c, uint8_t color)
{
	uint16_t c16 = c;
	uint16_t color16 = color;
	return c16 | color16 << 8;
}

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t *terminal_buffer;

/*
 * terminal_initialize
 *
 * Set the cursor to the top-left corner of the screen, make the text color light
 * and the background color black, and the terminal with whitespace.
 */
void terminal_initialize()
{
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = make_color(COLOR_LIGHT_GREY, COLOR_BLACK);
	terminal_buffer = (uint16_t *) 0xB8000;
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = make_vgaentry(' ', terminal_color);
		}
	}
}

void terminal_setcolor(uint8_t color)
{
	terminal_color = color;
}

void terminal_putentryat(char c, uint8_t color, size_t x, size_t y)
{
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = make_vgaentry(c, color);
}

/*
 * terminal_putchar
 *
 * Display a character c at the location of the cursor and move the cursor
 * appropriately or handle the behavior of special characters such as newlines
 * and tabs.
 *
 * TODO: support more special characters and implement scrolling.
 */
void terminal_putchar(char c)
{
	size_t index = terminal_row * VGA_WIDTH + terminal_column;
	size_t bytes = (terminal_row + 1) * VGA_WIDTH - index;
	switch (c) {
	case '\n':
		memsetw(&terminal_buffer[index], 0, bytes);
		terminal_column = 0;
		if (++terminal_row == VGA_HEIGHT) {
			terminal_column = 0;
			terminal_scroll();
		}
		break;
	case '\b':
		terminal_putentryat(0, terminal_color, terminal_column, terminal_row);
		if (terminal_column > 0) {
			terminal_putentryat(0, terminal_color, --terminal_column, terminal_row);
		} else {
			terminal_row--;
			for (terminal_column = 0;
				terminal_buffer[terminal_row * VGA_WIDTH + terminal_column] != 0;
				terminal_column++);
		}
		break;
	default:
		terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
		if (++terminal_column == VGA_WIDTH) {
			terminal_column = 0;
			if (++terminal_row == VGA_HEIGHT) {
				terminal_scroll();
			}
		}
		break;
	}
	terminal_putentryat('_', terminal_color, terminal_column, terminal_row);
}

void terminal_scroll()
{
	memcpy(terminal_buffer,
		&terminal_buffer[VGA_WIDTH],
		(VGA_HEIGHT - 1) * VGA_WIDTH * sizeof(*terminal_buffer));
	memsetw(&terminal_buffer[VGA_WIDTH * (VGA_HEIGHT - 1)],
		0, VGA_WIDTH * sizeof(*terminal_buffer));
	terminal_row = VGA_HEIGHT - 1;
}

void terminal_writestring(const char *data)
{
	size_t datalen = strlen(data);
	for (size_t i = 0; i < datalen; i++)
		terminal_putchar(data[i]);
}

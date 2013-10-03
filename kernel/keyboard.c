#include <printk.h>
#include <keyboard.h>

uint8_t inportb(uint16_t _port);

unsigned char kbd_us[128] = {
	0, 27,
	'1', '2', '3', '4', '5', '6', '7','8', '9', '0', '-', '=', '\b',
	'\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
	0, /* 29 - control */
	'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'',
	'`', 0, /* left shift */
	'\\',
	'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/',
	0, /* right shift */
	'*', 0, /* alt */
	' ', /* space bar */
	0, /* caps lock */
	0,  /* 59 - f1 key */
	0, 0, 0, 0, 0, 0, 0, 0,
	0, /* through f10 */
	0, /* 69 - num lock */
	0, /* scroll lock */
	0, /* home key */
	0, /* up arrow */
	0, /* page up */
	'-',
	0, /* left arrow */
	0,
	0, /* right arrow */
	'+',
	0, /* 79 end key */
	0, /* Down arrow */
	0, /* Page down */
	0, /* Insert key */
	0, /* Delete key */
	0, 0, 0,
	0, /* f11 key */
	0, /* f12 key */
	0, /* All other keys are undefined */
};

void keyboard_handler(struct regs *r)
{
	unsigned char scancode;

	scancode = inportb(0x60);

	if (scancode & 0x80) {
	} else {
		printk("%c", kbd_us[scancode]);
	}
}

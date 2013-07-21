#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <display.h>
#include <printk.h>

/*
 * Mail method invoked by boot.s
 */
void kernel_main()
{
	terminal_initialize();
	terminal_writestring("Hello, kernel world!\n");
	for (uint8_t i = 0; i < 30; i++) {
		printk("Iteration %d %x\n", i, i);
	}
}

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <display.h>
#include <printk.h>
#include <string.h>
#include <interrupt.h>
#include <gdt.h>

/*
 * Main function invoked by boot.s
 */
void kernel_main()
{
	terminal_initialize();
	gdt_install();
	idt_install();
	isrs_install();
	printk("Hello, kernel world!\n");
	for (int x = 5; x > -1; x--) {
		printk("%d\n", 4 / x);
	}
}

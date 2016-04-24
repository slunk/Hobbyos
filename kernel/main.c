#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <display.h>
#include <printk.h>
#include <string.h>
#include <interrupt.h>
#include <gdt.h>
#include <keyboard.h>
#include <page.h>
#include <irq.h>
#include <system.h>
#include <timer.h>

/*
 * Main function invoked by boot.s
 */
void kernel_main()
{
	terminal_initialize();
	gdt_install();
	idt_install();
	isrs_install();
	irq_install();
	timer_install();
	irq_install_handler(1, keyboard_handler);
	paging_install();
	__asm__ __volatile__ ("sti");
	printk("Hello, kernel world!\n");
	uint32_t *ptr = (uint32_t *) 0xA0000000;
	uint32_t do_page_fault = *ptr;
	printk("%d\n", do_page_fault);
	/*for (int x = 5; x > -1; x--) {
		printk("%d\n", 4 / x);
	}*/
	for(;;);
}

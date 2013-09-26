#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <display.h>
#include <printk.h>
#include <string.h>
#include <interrupt.h>
#include <gdt.h>

uint8_t inportb(uint16_t _port)
{
	uint8_t rv;
	__asm__ __volatile__ ("inb %1, %0" : "=a" (rv) : "dN" (_port));
	return rv;
}

void outportb(uint16_t _port, uint8_t _data)
{
	__asm__ __volatile__ ("outb %1, %0" : : "dN" (_port), "a" (_data));
}

extern void irq0();
extern void irq1();
extern void irq2();
extern void irq3();
extern void irq4();
extern void irq5();
extern void irq6();
extern void irq7();
extern void irq8();
extern void irq9();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();

void *irq_routines[16] = {0};

void irq_install_handler(int irq, void (*handler)(struct regs *r))
{
	irq_routines[irq] = handler;
}

void irq_uninstall_handler(int irq)
{
	irq_routines[irq] = 0;
}

void irq_remap()
{
	outportb(0x20, 0x11);
	outportb(0xA0, 0x11);
	outportb(0x21, 0x20);
	outportb(0xA1, 0x28);
	outportb(0x21, 0x04);
	outportb(0xA1, 0x02);
	outportb(0x21, 0x01);
	outportb(0xA1, 0x01);
	outportb(0x21, 0x0);
	outportb(0xA1, 0x0);
}

void irq_install()
{
	irq_remap();

	idt_set_gate(32, (unsigned)irq0, 0x08, 0x8E);
	idt_set_gate(33, (unsigned)irq1, 0x08, 0x8E);
	idt_set_gate(34, (unsigned)irq2, 0x08, 0x8E);
	idt_set_gate(35, (unsigned)irq3, 0x08, 0x8E);
	idt_set_gate(36, (unsigned)irq4, 0x08, 0x8E);
	idt_set_gate(37, (unsigned)irq5, 0x08, 0x8E);
	idt_set_gate(38, (unsigned)irq6, 0x08, 0x8E);
	idt_set_gate(39, (unsigned)irq7, 0x08, 0x8E);
	idt_set_gate(40, (unsigned)irq8, 0x08, 0x8E);
	idt_set_gate(41, (unsigned)irq9, 0x08, 0x8E);
	idt_set_gate(42, (unsigned)irq10, 0x08, 0x8E);
	idt_set_gate(43, (unsigned)irq11, 0x08, 0x8E);
	idt_set_gate(44, (unsigned)irq12, 0x08, 0x8E);
	idt_set_gate(45, (unsigned)irq13, 0x08, 0x8E);
	idt_set_gate(46, (unsigned)irq14, 0x08, 0x8E);
	idt_set_gate(47, (unsigned)irq15, 0x08, 0x8E);
}

void irq_handler(struct regs *r)
{
	void (*handler)(struct regs *r);

	handler = irq_routines[r->int_no - 32];

	if (handler) {
		handler(r);
	}

	if (r->int_no >= 40) {
		outportb(0xA0, 0x20);
	}

	outportb(0x20, 0x20);
}

void timer_phase(int hz)
{
	int divisor = 1193180 / hz;
	outportb(0x43, 0x36);
	outportb(0x40, divisor & 0xFF);
	outportb(0x40, divisor >> 8);
}

void timer_handler(struct regs *r)
{
	static int timer_ticks = 0;
	timer_ticks++;

	if (timer_ticks % 18 == 0) {
		printk("One second has passed\n");
	}
}

void timer_install()
{
	irq_install_handler(0, timer_handler);
}

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
	__asm__ __volatile__ ("sti");
	printk("Hello, kernel world!\n");
	for(;;);
	/*for (int x = 5; x > -1; x--) {
		printk("%d\n", 4 / x);
	}*/
}

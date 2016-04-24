#include <timer.h>
#include <system.h>
#include <irq.h>

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
		/* printk("One second has passed\n"); */
	}
}

void timer_install()
{
	irq_install_handler(0, timer_handler);
}

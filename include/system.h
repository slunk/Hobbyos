#ifndef _SYSTEM_H
#define _SYSTEM_H
#include <stddef.h>
#include <stdint.h>

struct regs {
	unsigned int gs, fs, es, ds;
	unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;
	unsigned int int_no, err_code;
	unsigned int eip, cs, eflags, useresp, ss;
};

void *memcpy(void *dest, const void *src, size_t count);

void *memset(void *dest, int val, size_t count);

unsigned char *memcpyb(unsigned char *dest, const unsigned char *src, size_t count);

unsigned char *memsetb(unsigned char *dest, unsigned char val, size_t count);

unsigned short *memsetw(unsigned short *dest, unsigned short val, int count);

unsigned char inportb(unsigned short _port);

void outportb(unsigned short _port, unsigned char _data);

#endif

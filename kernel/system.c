#include <system.h>

void *memcpy(void *dest, const void *src, size_t count)
{
    return memcpyb(dest, src, count);
}

void *memset(void *dest, int val, size_t count) {
    return memsetb(dest, (unsigned char)val, count);
}

unsigned char *memcpyb(unsigned char *dest, const unsigned char *src, size_t count)
{
    size_t i;
    for (i = 0; i < count; i++) {
        dest[i] = src[i];
    }
    return dest;
}

unsigned char *memsetb(unsigned char *dest, unsigned char val, size_t count)
{
    size_t i;
    for (i = 0; i < count; i++) {
        dest[i] = val;
    }
    return dest;
}

unsigned short *memsetw(unsigned short *dest, unsigned short val, int count)
{
    int i;
    for (i = 0; i < count; i++) {
        dest[i] = val;
    }
    return dest;
}

unsigned char inportb(unsigned short _port)
{
	uint8_t rv;
	__asm__ __volatile__ ("inb %1, %0" : "=a" (rv) : "dN" (_port));
	return rv;
}

void outportb(unsigned short _port, unsigned char _data)
{
	__asm__ __volatile__ ("outb %1, %0" : : "dN" (_port), "a" (_data));
}

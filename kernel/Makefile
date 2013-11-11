CC=/home/peter/opt/cross/bin/i586-elf-gcc
AS=/home/peter/opt/cross/bin/i586-elf-as

KERNEL=hobbyos.bin
CFLAGS=-std=gnu99 -ffreestanding -O2 -Wall -Wextra
CSOURCES=display.c main.c printk.c string.c interrupt.c gdt.c keyboard.c paging.c
ASM=boot.s
INCLUDE=../include
ISODIR=../isodir
OBJECTS=$(CSOURCES:.c=.o) $(ASM:.s=.o)

all: $(OBJECTS) linker.ld
	$(CC) -T linker.ld -o $(ISODIR)/boot/$(KERNEL) -ffreestanding -O2 -nostdlib $(OBJECTS) -lgcc	

.c.o:
	$(CC) -c $< -o $@ $(CFLAGS) -I $(INCLUDE)

.s.o:
	$(AS) $< -o $@

clean:
	rm -rf *.o $(ISODIR)/boot/$(KERNEL)

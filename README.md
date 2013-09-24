## Hobbyos

A toy operating system I'm writing to learn more about
os development. So far, the code is heavily based on the
"Bare Bones" tutorial on the os dev wiki (http://wiki.osdev.org/Bare_Bones),
and Bran's kernerl development tutorial (http://www.osdever.net/tutorials/view/brans-kernel-development-tutorial).

### Compilation

For now, you have to edit the first two lines of kernel/Makefile
to point to a i586-elf cross compiler and cross assembler on your
computer. Afterwards, just type in 'make' in the kernel directory.

### Running

    qemu-system-i386 -kernel isodir/boot/hobbyos.bin

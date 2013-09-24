# Multiboot boilerplate.
.set ALIGN,	1<<0
.set MEMINFO,	1<<1
.set FLAGS,	ALIGN | MEMINFO
.set MAGIC,	0x1BADB002
.set CHECKSUM,	-(MAGIC + FLAGS)

.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

# Reserve space for the stack.
.section .bootstrap_stack
stack_bottom:
.skip 16384
stack_top:

.section .text
.global _start
.type _start, @function
# Entry point of the kernel code. Set the stack pointer
# to the top of the stack space declared above and call
# our C code.
_start:
	movl $stack_top, %esp
	call kernel_main
	cli # Disable interrupts
	hlt # Halt
# Loop forever. If kernel_main returns for whatever reason,
# we need to be sure that the processor does not continue to
# execute whatever might come after this.
.Lhang:
	jmp .Lhang

.size _start, . - _start

# Replace the gdt created by the bios with our own.
.global gdt_flush
gdt_flush:
	lgdt (gp)
	movl $0x10, %eax
	movl %eax, %ds
	movl %eax, %es
	movl %eax, %fs
	movl %eax, %gs
	movl %eax, %ss
	jmp $0x08,$flush2
flush2:
	ret

# Tell the processor where our IDT is located.
.global idt_load
idt_load:
	lidt (idtp)
	ret

# Boilerplate interrupt handler stubs.
# Each one pushes an interrupt number to the stack.
# Some also push a dummy error code so that our C code
# can rely on a consistent set of parameters always
# being passed to it.
.global isr0
.global isr1
.global isr2
.global isr3
.global isr4
.global isr5
.global isr6
.global isr7
.global isr8
.global isr9
.global isr10
.global isr11
.global isr12
.global isr13
.global isr14
.global isr15
.global isr16
.global isr17
.global isr18
.global isr19
.global isr20
.global isr21
.global isr22
.global isr23
.global isr24
.global isr25
.global isr26
.global isr27
.global isr28
.global isr29
.global isr30
.global isr31

isr0:
	cli
	pushl $0
	pushl $0
	jmp isr_common_stub

isr1:
	cli
	pushl $0
	pushl $1
	jmp isr_common_stub

isr2:
	cli
	pushl $0
	pushl $2
	jmp isr_common_stub

isr3:
	cli
	pushl $0
	pushl $3
	jmp isr_common_stub

isr4:
	cli
	pushl $0
	pushl $4
	jmp isr_common_stub

isr5:
	cli
	pushl $0
	pushl $5
	jmp isr_common_stub

isr6:
	cli
	pushl $0
	pushl $6
	jmp isr_common_stub

isr7:
	cli
	pushl $0
	pushl $7
	jmp isr_common_stub

isr8:
	cli
	pushl $8
	jmp isr_common_stub

isr9:
	cli
	pushl $9
	jmp isr_common_stub

isr10:
	cli
	pushl $10
	jmp isr_common_stub

isr11:
	cli
	pushl $11
	jmp isr_common_stub

isr12:
	cli
	pushl $12
	jmp isr_common_stub

isr13:
	cli
	pushl $13
	jmp isr_common_stub

isr14:
	cli
	pushl $14
	jmp isr_common_stub

isr15:
	cli
	pushl $15
	jmp isr_common_stub

isr16:
	cli
	pushl $16
	jmp isr_common_stub

isr17:
	cli
	pushl $17
	jmp isr_common_stub

isr18:
	cli
	pushl $18
	jmp isr_common_stub

isr19:
	cli
	pushl $19
	jmp isr_common_stub

isr20:
	cli
	pushl $20
	jmp isr_common_stub

isr21:
	cli
	pushl $21
	jmp isr_common_stub

isr22:
	cli
	pushl $22
	jmp isr_common_stub

isr23:
	cli
	pushl $23
	jmp isr_common_stub

isr24:
	cli
	pushl $24
	jmp isr_common_stub

isr25:
	cli
	pushl $25
	jmp isr_common_stub

isr26:
	cli
	pushl $26
	jmp isr_common_stub

isr27:
	cli
	pushl $27
	jmp isr_common_stub

isr28:
	cli
	pushl $28
	jmp isr_common_stub

isr29:
	cli
	pushl $29
	jmp isr_common_stub

isr30:
	cli
	pushl $30
	jmp isr_common_stub

isr31:
	cli
	pushl $31
	jmp isr_common_stub

# Push registers to the stack and call C fault_handler
isr_common_stub:
	pusha # Push edi, esi, ebp, esp, ebx, edx, ecx, and eax to the stack
	pushl %ds
	pushl %es
	pushl %fs
	pushl %gs
	movl $0x10, %eax
	movl %eax, %ds
	movl %eax, %es
	movl %eax, %fs
	movl %eax, %gs
	movl %esp, %eax
	pushl %eax
	call fault_handler
	;movl fault_handler, %eax
	;call *%eax
	popl %eax
	popl %gs
	popl %fs
	popl %es
	popl %ds
	popa
	addl $8, %esp
	iret

.global irq0
.global irq1
.global irq2
.global irq3
.global irq4
.global irq5
.global irq6
.global irq7
.global irq8
.global irq9
.global irq10
.global irq11
.global irq12
.global irq13
.global irq14
.global irq15

irq0:
	cli
	pushl $0
	pushl $32
	jmp irq_common_stub

irq1:
	cli
	pushl $0
	pushl $33
	jmp irq_common_stub

irq2:
	cli
	pushl $0
	pushl $34
	jmp irq_common_stub

irq3:
	cli
	pushl $0
	pushl $35
	jmp irq_common_stub

irq4:
	cli
	pushl $0
	pushl $36
	jmp irq_common_stub

irq5:
	cli
	pushl $0
	pushl $37
	jmp irq_common_stub

irq6:
	cli
	pushl $0
	pushl $38
	jmp irq_common_stub

irq7:
	cli
	pushl $0
	pushl $39
	jmp irq_common_stub

irq8:
	cli
	pushl $0
	pushl $40
	jmp irq_common_stub

irq9:
	cli
	pushl $0
	pushl $41
	jmp irq_common_stub

irq10:
	cli
	pushl $0
	pushl $42
	jmp irq_common_stub

irq11:
	cli
	pushl $0
	pushl $43
	jmp irq_common_stub

irq12:
	cli
	pushl $0
	pushl $44
	jmp irq_common_stub

irq13:
	cli
	pushl $0
	pushl $45
	jmp irq_common_stub

irq14:
	cli
	pushl $0
	pushl $46
	jmp irq_common_stub

irq15:
	cli
	pushl $0
	pushl $47
	jmp irq_common_stub

irq_common_stub:
	pusha
	pushl %ds
	pushl %es
	pushl %fs
	pushl %gs
	movl $0x10, %eax
	movl %eax, %ds
	movl %eax, %es
	movl %eax, %fs
	movl %eax, %gs
	movl %esp, %eax
	pushl %eax
	call irq_handler
	popl %eax
	popl %gs
	popl %fs
	popl %es
	popl %ds
	popa
	addl $8, %esp
	iret

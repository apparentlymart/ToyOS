# Constants for multiboot header
.set ALIGN,    1<<0             # align loaded modules on page boundaries
.set MEMINFO,  1<<1             # provide memory map
.set FLAGS,    ALIGN | MEMINFO  # this is the Multiboot 'flag' field
.set MAGIC,    0x1BADB002       # 'magic number' lets bootloader find the header
.set CHECKSUM, -(MAGIC + FLAGS) # checksum of above, to prove we are multiboot

# Multiboot header
.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

# Allocate a 16k stack
.section .bootstrap_stack, "aw", @nobits
stack_bottom:
.skip 16384
stack_top:

# Entry point (specified in linker script)
.section .text
.global _start
.type _start, @function
_start:
    # Set stack pointer to the top of the stack.
	movl $stack_top, %esp

    # Call the "main" function in main.c
	call main

    # If main returns -- which it really shouldnt -- then we'll just halt.
	cli
	hlt
.Lhang:
	jmp .Lhang

# Size of the start routine.
.size _start, . - _start

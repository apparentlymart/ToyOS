ENTRY(_start)

SECTIONS
{
    /* Start at 1MB, as is conventional. */
	. = 1M;

	/* Multiboot header, followed by code */
	.text BLOCK(4K) : ALIGN(4K)
	{
		*(.multiboot)
		*(.text)
	}

	/* Read-only data */
	.rodata BLOCK(4K) : ALIGN(4K)
	{
		*(.rodata)
	}

	/* Initialized read/write data */
	.data BLOCK(4K) : ALIGN(4K)
	{
		*(.data)
	}

	/* Uninitialized read/write data, including the stack */
	.bss BLOCK(4K) : ALIGN(4K)
	{
		*(COMMON)
		*(.bss)
		*(.bootstrap_stack)
	}
}

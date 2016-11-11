ENTRY(_start)

SECTIONS
{
	. = 1M;

	.text BLOCK(4K) : ALIGN(4K)
	{
		stext = .;

		*(.multiboot)
		*(.text)
	}

	.rodata BLOCK(4K) : ALIGN(4K)
	{
		*(.rodata)
	}

	.data BLOCK(4K) : ALIGN(4K)
	{
		*(.data)

		edata = .;
	}

	.bss BLOCK(4K) : ALIGN(4K)
	{
		sbss = .;

		*(COMMON)
		*(.bss)

		ebss = .;
		end_kernel = .;
	}
}
